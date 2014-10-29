#include "Database.hpp"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

#include <cstring>
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <list>

using namespace sql;

const char* databaseStr = "localhost";
const char* databaseUserName = "user";
const char* databaseUserPassword = "user";
const char* databaseSchema = "csci222";

const char* noDB = "Sorry, but was unable to open database so operation failed";

const char* prepareFailed = "Failure when preparing statement";
const char* bindFailed = "Failure when binding arguments";
const char* writeFailed = "Failure when writing to database";

Database::Database()
{
        // Constructors should always succeed. But suppose it failed and
        // the database couldn't be created?
        invalid = true;
        driver = get_driver_instance();
        try {
                dbcon = driver->connect(databaseStr, databaseUserName, databaseUserPassword);
        } catch (sql::SQLException &e) {
                // Failed
                return;
        }
        dbcon->setSchema(databaseSchema);
        // It's ok
        invalid = false;
}

Database::~Database()
{
        if (!invalid) {
                this->close();
        }
}

void Database::close()
{
        if (!invalid) {
                dbcon->close();
                delete dbcon;
        }
        invalid = true;
}

User Database::fetchUser(std::string key, std::string confName) throw (const char*)
{
        if (invalid)
                throw (noDB);

	// Add information on user from database to User object
	const char* getUser = "SELECT * FROM UserAccount WHERE username=?";
	const char* getPersonalInfo = "SELECT * FROM PersonalInfo WHERE userID=?";
	const char* getExpertise = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT expertiseID FROM ExpertiseArea WHERE userID=?)";
        const char* getUserType = "SELECT userType FROM UserType WHERE (userID=? and confID=(SELECT confID FROM Conference WHERE name=?))";

        // =======================================
        // user account
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUser);
	pstmt->setString(1, key);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return User();
	}
        
        int userID = rs->getInt(1);
        std::string username = rs->getString(2);
        std::string password = rs->getString(3);

        delete rs;
        delete pstmt;

        // =======================================
        // Personal Info
	pstmt = dbcon->prepareStatement(getPersonalInfo);
	pstmt->setInt(1, userID);
	rs = pstmt->executeQuery();
	haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return User();
	}
        
        std::string name = rs->getString(3);
	std::string email = rs->getString(4);
	std::string organisation = rs->getString(5);
	std::string phone = rs->getString(6);

        delete rs;
        delete pstmt;

        // =======================================
        // Expertise Area
        std::vector<std::string> vec;
	
	pstmt = dbcon->prepareStatement(getExpertise);
	pstmt->setInt(1, userID);
	rs = pstmt->executeQuery();
        
        while (rs->next()) {
                std::string expertise = rs->getString(1);
                vec.push_back(expertise);
        }
        
        // =======================================
        // user type 
        UserType_t userType = AUTHOR;
        
	pstmt = dbcon->prepareStatement(getUserType);

        pstmt->setInt(1, userID);
	pstmt->setString(2, confName);

	rs = pstmt->executeQuery();

	haveRecord = rs->next();
	if (haveRecord)
	{
            int e = rs->getInt(1);            
            if (e = 1)
                userType = AUTHOR;
            else if (e = 2)
                userType = REVIEWER;
            else if (e = 3)
                userType = PCCHAIR;
	}
        delete rs;
        delete pstmt;
        
        User user(
		username,
		name,
		email,
		organisation,
		phone,
		password,
		userID,
		vec,
                userType);

	return user;
}

bool Database::existsUserName(std::string key) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* countUser = "SELECT COUNT(*) FROM UserAccount WHERE username=?";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(countUser);

        int count = 0;
        pstmt->setString(1, key);
        rs = pstmt->executeQuery();

        if (rs->next()) {
                count = rs->getInt(1);
        }
        delete rs;
        delete pstmt;

        return count == 1;
}

void Database::putUser(std::string key, User user) throw (const char*)
{
        if (invalid)
                throw (noDB);

        if (this->existsUserName(key))
	{
                this->updateUser(user);
        }
	else
	{
        	this->createUser(user);
	}
}

void Database::createUser(User user)
{
        if (invalid)
                throw (noDB);

	const char* insertPersonalInfo = "INSERT INTO PersonalInfo(userID, name, email, organisation, phone) VALUES(NULL, ?, ?, ?, ?)";
	const char* insertUser = "INSERT INTO UserAccount(username, password, infoID) VALUES(?, ?, LAST_INSERT_ID())";
	const char* updatePIuserID = "UPDATE PersonalInfo SET userID = LAST_INSERT_ID() WHERE infoID=(SELECT infoID FROM UserAccount WHERE userID=LAST_INSERT_ID())";
	const char* getUserID = "SELECT LAST_INSERT_ID()";
	const char* insertExpertise = "INSERT IGNORE INTO ExpertiseArea VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Personal Info
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(insertPersonalInfo);
        pstmt->setString(1, user.name);
        pstmt->setString(2, user.email);
        pstmt->setString(3, user.organisation);
        pstmt->setString(4, user.phone);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // user account
        pstmt = dbcon->prepareStatement(insertUser);
        pstmt->setString(1, user.userName);
        pstmt->setString(2, user.password);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Personal Info Update
        pstmt = dbcon->prepareStatement(updatePIuserID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Store userID
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserID);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int userID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Expertise
      	if (user.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertExpertise);
    		std::vector<std::string>::const_iterator it;
      		for (it = user.keywords.begin(); it != user.keywords.end(); it ++)
		    {
			    std::string word = *it;	

        	    	if (!this->existsKeyword(word))
			    {
			    	this->addKeyword(word);
			    }
			    
			    pstmt->setInt(1, userID);
			    pstmt->setString(2, word);

      		            pstmt->executeUpdate();
		    }
      		delete pstmt;

      	}
}

void Database::updateUser(User user)
{
        if (invalid)
                throw (noDB);

	const char* getUserID = "SELECT userID FROM UserAccount WHERE username = ?";
	const char* updateUser = "UPDATE UserAccount SET username=?, password=? WHERE userID=?";
	const char* updatePersonalInfo = "UPDATE PersonalInfo SET name=?, email=?, organisation=?, phone=? WHERE infoID=?";

        const char* deleteExpertise = "DELETE FROM ExpertiseArea WHERE userID=?";
	const char* insertExpertise = "INSERT IGNORE INTO ExpertiseArea VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Store userID
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserID);
        pstmt->setString(1, user.userName);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int userID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // user account
        pstmt = dbcon->prepareStatement(updateUser);
        pstmt->setString(1, user.userName);
        pstmt->setString(2, user.password);
        pstmt->setInt(3, userID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Personal Info
        pstmt = dbcon->prepareStatement(updatePersonalInfo);
        pstmt->setString(1, user.name);
        pstmt->setString(2, user.email);
        pstmt->setString(3, user.organisation);
        pstmt->setString(4, user.phone);
        pstmt->setInt(5, userID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Expertise Delete
        pstmt = dbcon->prepareStatement(deleteExpertise);
        pstmt->setInt(1, userID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Expertise Insert
      	if (user.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertExpertise);
		    std::vector<std::string>::const_iterator it;
      		for (it = user.keywords.begin(); it != user.keywords.end(); it ++)
		    {
		    	std::string word = *it;	
            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	pstmt->setInt(1, userID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;

      	}
}

std::vector<int> Database::allUserIDs()
{
        if (invalid)
                throw (noDB);
        std::vector<int> vptr;

        const char* selectall = "select userID from UserAccount";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                int anid = rs->getInt(1);
                vptr.push_back(anid);
        }

        return vptr;
}

std::vector<std::string> Database::allUserNames()
{
        if (invalid)
                throw (noDB);
        std::vector<std::string> vptr;

        const char* selectall = "select username from UserAccount";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                std::string aname = rs->getString(1);
                vptr.push_back(aname);
        }

        return vptr;
}

void Database::setUserAsAuthor(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);
    
    const char* insertChairType = "INSERT INTO UserType VALUES(?, ?, 'author')";
    
    // ======================================
    // insert new userType
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(insertChairType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();

    delete pstmt;
}

void Database::updateUserAsAuthor(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);

    const char* updateCurrentType = "UPDATE UserType SET userType='author' WHERE (userID=? and confID=?)";

    // =====================================
    // remove current type(s) for matching userID, confID
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(updateCurrentType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();
    
    delete pstmt;
}

void Database::setUserAsPC(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);
    
    const char* insertChairType = "INSERT INTO UserType VALUES(?, ?, 'pc')";
    
    // ======================================
    // insert new userType
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(insertChairType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();

    delete pstmt;
}

void Database::updateUserAsPC(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);

    const char* updateCurrentType = "UPDATE UserType SET userType='pc' WHERE (userID=? and confID=?)";

    // =====================================
    // remove current type(s) for matching userID, confID
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(updateCurrentType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();
    
    delete pstmt;
}

void Database::setUserAsChair(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);
    
    const char* insertChairType = "INSERT INTO UserType VALUES(?, ?, 'chair')";
    
    // ======================================
    // insert new userType
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(insertChairType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();

    delete pstmt;
}

void Database::updateUserAsChair(int userID, int confID) throw (const char*)
{
    if (invalid)
        throw (noDB);

    const char* updateCurrentType = "UPDATE UserType SET userType='chair' WHERE (userID=? and confID=?)";

    // =====================================
    // remove current type(s) for matching userID, confID
    sql::PreparedStatement *pstmt = NULL;

    pstmt = dbcon->prepareStatement(updateCurrentType);
    pstmt->setInt(1, userID);
    pstmt->setInt(2, confID);

    pstmt->executeUpdate();
    
    delete pstmt;
}

bool Database::existsKeyword(std::string key) throw (const char*)
{
    if (invalid)
        throw (noDB);

	const char* countKeyword = "SELECT COUNT(*) FROM Keywords WHERE keyword=?";

    sql::PreparedStatement *pstmt = NULL;
    sql::ResultSet * rs = NULL;

    pstmt = dbcon->prepareStatement(countKeyword);

    int count = 0;
    pstmt->setString(1, key);
    rs = pstmt->executeQuery();

    if (rs->next()) {
            count = rs->getInt(1);
    }
    delete rs;
    delete pstmt;

    return count == 1;
}

void Database::addKeyword(std::string key) throw (const char*)
{
	if (invalid)
		throw (noDB);

	const char* insertKeyword = "INSERT INTO Keywords VALUES(NULL, ?)";

        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(insertKeyword);
        pstmt->setString(1, key);

        pstmt->executeUpdate();

        delete pstmt;
}

Conference Database::fetchConference(std::string key) throw (const char*)
{
        if (invalid)
                throw (noDB);

	// Add information on user from database to User object
	const char* getConference = "SELECT * FROM Conference WHERE name=?";
	const char* getConfKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT keywordID FROM ConferenceKeywords WHERE confID=?)";

        // =======================================
        // Conference 
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getConference);
	pstmt->setString(1, key);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return Conference();
	}

        int confID = rs->getInt(1);
        std::string title = rs->getString(2);
        std::string topic = rs->getString(3);
        std::string description = rs->getString(4);
        std::string location = rs->getString(5);
        bool isActive = rs->getBoolean(6);
        int paperDeadlineD  = rs->getInt(7);
        int paperDeadlineM  = rs->getInt(8);
        int paperDeadlineY  = rs->getInt(9);
	Date paperDeadline(paperDeadlineD, paperDeadlineM, paperDeadlineY);
        bool isBeforePaperDeadline = rs->getBoolean(10);
        int allocationDateD  = rs->getInt(11);
        int allocationDateM  = rs->getInt(12);
        int allocationDateY  = rs->getInt(13);
	Date allocationDate(allocationDateD, allocationDateM, allocationDateY);
        bool isBeforeAllocationDate = rs->getBoolean(14);
        int reviewDeadlineSoftD  = rs->getInt(15);
        int reviewDeadlineSoftM  = rs->getInt(16);
        int reviewDeadlineSoftY  = rs->getInt(17);
	Date reviewDeadlineSoft(reviewDeadlineSoftD, reviewDeadlineSoftM, reviewDeadlineSoftY);
        bool isBeforeSoftReviewDeadline = rs->getBoolean(18);
	int reviewDeadlineHardD  = rs->getInt(19);
        int reviewDeadlineHardM  = rs->getInt(20);
        int reviewDeadlineHardY  = rs->getInt(21);
	Date reviewDeadlineHard(reviewDeadlineHardD, reviewDeadlineHardM, reviewDeadlineHardY);
        bool isBeforeHardReviewDeadline = rs->getBoolean(22);
        int discussDeadlineD  = rs->getInt(23);
        int discussDeadlineM  = rs->getInt(24);
        int discussDeadlineY  = rs->getInt(25);
	Date discussDeadline(discussDeadlineD, discussDeadlineM, discussDeadlineY);
        bool isBeforeDiscussDeadline = rs->getBoolean(26);
	int reviewersPerPaper = rs->getInt(27);
	int postWordLimit = rs->getInt(28);

        delete rs;
        delete pstmt;

        // =======================================
        // Expertise Area
        std::vector<std::string> vec;
	
	pstmt = dbcon->prepareStatement(getConfKeywords);
	pstmt->setInt(1, confID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                vec.push_back(keyword);
        }

        delete rs;
        delete pstmt;

        Conference conf(
		isActive,
		title,
		confID,
		topic,
		description,
		location,
		vec,
		isBeforePaperDeadline,
		paperDeadline,
		isBeforeAllocationDate,
		allocationDate,
		isBeforeSoftReviewDeadline,
		reviewDeadlineSoft,
		isBeforeHardReviewDeadline,
		reviewDeadlineHard,
		isBeforeDiscussDeadline,
		discussDeadline,
		reviewersPerPaper,
		postWordLimit
		);
	
	return conf;
}

bool Database::existsConfName(std::string key) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* countConf = "SELECT COUNT(*) FROM Conference WHERE name=?";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(countConf);

        int count = 0;
        pstmt->setString(1, key);
        rs = pstmt->executeQuery();

        if (rs->next()) {
                count = rs->getInt(1);
        }
        delete rs;
        delete pstmt;

        return count == 1;
}

void Database::putConf(std::string key, Conference conf) throw (const char*)
{
        if (invalid)
                throw (noDB);

        if (this->existsConfName(key))
	{
                this->updateConf(conf);
        }
	else
	{
        	this->createConf(conf);
	}
}

void Database::createConf(Conference conf)
{
        if (invalid)
                throw (noDB);

	const char* insertConference = "INSERT INTO Conference(confID, name, topic, description, location, active, paperDeadlineD, paperDeadlineM, paperDeadlineY, paperDeadlineBool, allocationDateD, allocationDateM, allocationDateY, allocationDateBool, reviewDeadlineSoftD, reviewDeadlineSoftM, reviewDeadlineSoftY, reviewDeadlineSoftBool, reviewDeadlineHardD, reviewDeadlineHardM, reviewDeadlineHardY, reviewDeadlineHardBool, discussDeadlineD, discussDeadlineM, discussDeadlineY, discussDeadlineBool, reviewersPerPaper, postWordlimit) VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	const char* getconfID = "SELECT LAST_INSERT_ID()";
	const char* insertConfKeyword = "INSERT IGNORE INTO ConferenceKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Personal Info
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(insertConference);

        pstmt->setString(1, conf.title);
        pstmt->setString(2, conf.topic);
        pstmt->setString(3, conf.description);
        pstmt->setString(4, conf.location);
        pstmt->setBoolean(5, conf.isActive);
        pstmt->setInt(6, conf.paperDeadline.getDay());
        pstmt->setInt(7, conf.paperDeadline.getMonth());
        pstmt->setInt(8, conf.paperDeadline.getYear());
        pstmt->setBoolean(9, conf.isBeforePaperDeadline);
        pstmt->setInt(10, conf.allocationDate.getDay());
        pstmt->setInt(11, conf.allocationDate.getMonth());
        pstmt->setInt(12, conf.allocationDate.getYear());
        pstmt->setBoolean(13, conf.isBeforeAllocationDate);
        pstmt->setInt(14, conf.reviewDeadlineSoft.getDay());
        pstmt->setInt(15, conf.reviewDeadlineSoft.getMonth());
        pstmt->setInt(16, conf.reviewDeadlineSoft.getYear());
        pstmt->setBoolean(17, conf.isBeforeSoftReviewDeadline);
        pstmt->setInt(18, conf.reviewDeadlineHard.getDay());
        pstmt->setInt(19, conf.reviewDeadlineHard.getMonth());
        pstmt->setInt(20, conf.reviewDeadlineHard.getYear());
        pstmt->setBoolean(21, conf.isBeforeHardReviewDeadline);
        pstmt->setInt(22, conf.discussDeadline.getDay());
        pstmt->setInt(23, conf.discussDeadline.getMonth());
        pstmt->setInt(24, conf.discussDeadline.getYear());
        pstmt->setBoolean(25, conf.isBeforeDiscussDeadline);
	pstmt->setInt(26, conf.reviewersPerPaper);
	pstmt->setInt(27, conf.postWordLimit);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Store confID
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getconfID);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int confID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Expertise
      	if (conf.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertConfKeyword);
		    std::vector<std::string>::const_iterator it;
      		for (it = conf.keywords.begin(); it != conf.keywords.end(); it ++)
		    {
		    	std::string word = *it;	

            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	
		    	pstmt->setInt(1, confID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;

      	}
}

void Database::updateConf(Conference conf)
{
        if (invalid)
                throw (noDB);

	const char* getConfID = "SELECT confID FROM Conference WHERE name = ?";

	const char* updateConference = "UPDATE Conference SET name=?, topic=?, description=?, location=?, active=?, paperDeadlineD=?, paperDeadlineM=?, paperDeadlineY=?, paperDeadlineBool=?, allocationDateD=?, allocationDateM=?, allocationDateY=?, allocationDateBool=?, reviewDeadlineSoftD=?, reviewDeadlineSoftM=?, reviewDeadlineSoftY=?, reviewDeadlineSoftBool=?, reviewDeadlineHardD=?, reviewDeadlineHardM=?, reviewDeadlineHardY=?, reviewDeadlineHardBool=?, discussDeadlineD=?, discussDeadlineM=?, discussDeadlineY=?, discussDeadlineBool=?, reviewersPerPaper=?, postWordlimit=? WHERE confID=?";

        const char* deleteKeywords = "DELETE FROM ConferenceKeywords WHERE confID=?";
	const char* insertKeywords = "INSERT IGNORE INTO ConferenceKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Store confID
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getConfID);
        pstmt->setString(1, conf.title);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int confID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Conference
        pstmt = dbcon->prepareStatement(updateConference);

        pstmt->setString(1, conf.title);
        pstmt->setString(2, conf.topic);
        pstmt->setString(3, conf.description);
        pstmt->setString(4, conf.location);
        pstmt->setBoolean(5, conf.isActive);
	int day = conf.paperDeadline.getDay();
	int month = conf.paperDeadline.getMonth();
	int year = conf.paperDeadline.getYear();
        pstmt->setInt(6, day);
        pstmt->setInt(7, month);
        pstmt->setInt(8, year);
        pstmt->setBoolean(9, conf.isBeforePaperDeadline);
        pstmt->setInt(10, conf.allocationDate.getDay());
        pstmt->setInt(11, conf.allocationDate.getMonth());
        pstmt->setInt(12, conf.allocationDate.getYear());
        pstmt->setBoolean(13, conf.isBeforeAllocationDate);
        pstmt->setInt(14, conf.reviewDeadlineSoft.getDay());
        pstmt->setInt(15, conf.reviewDeadlineSoft.getMonth());
        pstmt->setInt(16, conf.reviewDeadlineSoft.getYear());
        pstmt->setBoolean(17, conf.isBeforeSoftReviewDeadline);
        pstmt->setInt(18, conf.reviewDeadlineHard.getDay());
        pstmt->setInt(19, conf.reviewDeadlineHard.getMonth());
        pstmt->setInt(20, conf.reviewDeadlineHard.getYear());
        pstmt->setBoolean(21, conf.isBeforeHardReviewDeadline);
        pstmt->setInt(22, conf.discussDeadline.getDay());
        pstmt->setInt(23, conf.discussDeadline.getMonth());
        pstmt->setInt(24, conf.discussDeadline.getYear());
        pstmt->setBoolean(25, conf.isBeforeDiscussDeadline);
	pstmt->setInt(26, conf.reviewersPerPaper);
	pstmt->setInt(27, conf.postWordLimit);
	pstmt->setInt(28, confID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Keywords Delete
        pstmt = dbcon->prepareStatement(deleteKeywords);
        pstmt->setInt(1, confID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Keywords Insert
      	if (conf.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertKeywords);
		    std::vector<std::string>::const_iterator it;
      		for (it = conf.keywords.begin(); it != conf.keywords.end(); it ++)
		    {
		    	std::string word = *it;	
            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	pstmt->setInt(1, confID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;
      	}
}

std::vector<int> Database::allConfIDs()
{
        if (invalid)
                throw (noDB);
        std::vector<int> vptr;

        const char* selectall = "select confID from Conference";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                int anid = rs->getInt(1);
                vptr.push_back(anid);
        }

        return vptr;
}

std::vector<std::string> Database::allConfNames()
{
        if (invalid)
                throw (noDB);
        std::vector<std::string> vptr;

        const char* selectall = "select name from Conference";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                std::string aname = rs->getString(1);
                vptr.push_back(aname);
        }

        return vptr;
}

std::vector<int> Database::activeConfIDs()
{
        if (invalid)
                throw (noDB);
        std::vector<int> vptr;

        const char* selectActive = "SELECT confID FROM Conference WHERE active = 1";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectActive);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                int anid = rs->getInt(1);
                vptr.push_back(anid);
        }

        return vptr;
}

std::vector<std::string> Database::activeConfNames()
{
        if (invalid)
                throw (noDB);
        std::vector<std::string> vptr;

        const char* selectActive = "SELECT name FROM Conference WHERE active = 1";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectActive);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                std::string aname = rs->getString(1);
                vptr.push_back(aname);
        }

        return vptr;
}

PaperSummary Database::fetchPaperSummary(int key) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperSummary = "SELECT paperName FROM Paper WHERE paperID=?";

        // =======================================
        // Paper Summary 
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperSummary);
	pstmt->setInt(1, key);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return PaperSummary();
	}

        std::string paperName = rs->getString(1);

        delete rs;
        delete pstmt;

        PaperSummary papSum(key, paperName);
	
	return papSum;
}

std::vector<PaperSummary> Database::allAuthorsPaperSummary(int confID, int leadAuthorID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperSummary = "SELECT paperName, paperID FROM Paper WHERE (confID=? and leadAuthorID=?)";

        // =======================================
        // Paper Summary 
	std::vector<PaperSummary> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperSummary);
	pstmt->setInt(1, confID);
	pstmt->setInt(2, leadAuthorID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
        	std::string paperName = rs->getString(1);
        	int paperID = rs->getInt(2);
        	PaperSummary papSum(paperID, paperName);
                vec.push_back(papSum);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

Paper Database::fetchPaper(int key) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaper = "SELECT * FROM Paper WHERE paperID=?";
	const char* getConfKeyword = "SELECT keyword FROM Keywords WHERE keywordID=(SELECT keywordID FROM Paper WHERE paperID=?)";
	const char* getPaperKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT keywordID FROM PaperKeywords WHERE paperID=?)";
	
	const char* getAuthors = "SELECT infoID, name, email, organisation, phone FROM PersonalInfo WHERE infoID IN (SELECT authorID FROM paperAuthors WHERE paperID=?)";

	const char* getDiscussPost = "SELECT comment, reviewerID, commentID FROM ReviewerDiscussion WHERE (paperID=? and confID=?)";

	const char* getReviews = "SELECT * FROM Review WHERE (paperID=? and confID=?)";
	
        // =======================================
        // Paper
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaper);
	pstmt->setInt(1, key);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return Paper();
	}

    	int paperID = rs->getInt(1);
	int confID = rs->getInt(3);
    	int leadAuthorID = rs->getInt(2);
    	std::string title = rs->getString(5);
    	std::string abstract = rs->getString(6);

        delete rs;
        delete pstmt;

        // =======================================
        // confKeyword
	pstmt = dbcon->prepareStatement(getConfKeyword);
	pstmt->setInt(1, key);

	rs = pstmt->executeQuery();

	haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return Paper();
	}

	std::string confKeyword = rs->getString(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Paper Keywords
        std::vector<std::string> keywords;
	
	pstmt = dbcon->prepareStatement(getPaperKeywords);
	pstmt->setInt(1, key);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                keywords.push_back(keyword);
        }

        delete rs;
        delete pstmt;

        // =======================================
        // Authors 
        std::vector<PersonalInfo> authors;
	
	pstmt = dbcon->prepareStatement(getAuthors);
	pstmt->setInt(1, key);
	rs = pstmt->executeQuery();

        while (rs->next()) {
		int infoID = rs->getInt(1);
		std::string name = rs->getString(2);
		std::string email = rs->getString(3);
		std::string organisation = rs->getString(4);
		std::string phone = rs->getString(5);
		PersonalInfo pInfo(name, email, organisation, phone, infoID);
                authors.push_back(pInfo);
        }

        delete rs;
        delete pstmt;

        // =======================================
        // Discussion
        Discussion discussion;
	
	pstmt = dbcon->prepareStatement(getDiscussPost);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		std::string comment = rs->getString(1);
		int reviewerID = rs->getInt(2);
		int commentID = rs->getInt(3);
		DiscussionPost discuss(comment, reviewerID, commentID);
                discussion.discussion.push_back(discuss);
        }

        delete rs;
        delete pstmt;

        // =======================================
        // Reviews
        std::vector<Review> reviews;
	
	pstmt = dbcon->prepareStatement(getReviews);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int reviewerID = rs->getInt(3);
		int overall = rs->getInt(5);
		int confidence = rs->getInt(6);
		int relevance = rs->getInt(7);
		int originality = rs->getInt(8);
		int significance = rs->getInt(9);
		int presentation = rs->getInt(10);
		int techQuality = rs->getInt(11);
		int evaluation = rs->getInt(12);
  		std::string commentsStrength = rs->getString(13);
  		std::string commentsWeakness = rs->getString(14);
  		std::string commentsSuggestions = rs->getString(15);
  		std::string commentsShortPaper = rs->getString(16);
  		std::string commentsBestAward = rs->getString(17);

		Review review(paperID, 
			reviewerID, 
			overall, 
			confidence, 
			relevance, 
			originality, 
			significance, 
			presentation, 
			techQuality, 
			evaluation, 
			commentsStrength, 
			commentsWeakness, 
			commentsSuggestions, 
			commentsShortPaper, 
			commentsBestAward);
		reviews.push_back(review);
        }

        delete rs;
        delete pstmt;

	Paper paper(
		paperID,
		confID,
		leadAuthorID,
		title,
		abstract,
		authors,
		keywords,
		confKeyword,
		reviews,
		discussion);

	return paper;
}

bool Database::existsPaperTitleConf(Paper paper) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* countPaper = "SELECT COUNT(*) FROM Paper WHERE (paperTitle=? and confID=?)";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(countPaper);

        int count = 0;
        pstmt->setString(1, paper.title);
        pstmt->setInt(2, paper.confID);

        rs = pstmt->executeQuery();

        if (rs->next()) {
                count = rs->getInt(1);
        }
        delete rs;
        delete pstmt;

        return count == 1;
}
void Database::createPaper(Paper paper, std::string pdf) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertPaper = "INSERT IGNORE INTO Paper(leadAuthorID, confID, keywordID, paperTitle, paperAbstract, paper) VALUES(?, ?, (SELECT keywordID FROM Keywords WHERE keyword=?), ?, ?, ?)";
	const char* getPaperID = "SELECT LAST_INSERT_ID()";
	const char* insertAuthors = "INSERT IGNORE INTO paperAuthors(paperID, authorID) VALUES(?, ?)";

	const char* insertKeywords = "INSERT IGNORE INTO PaperKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Paper
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(insertPaper);
        pstmt->setInt(1, paper.leadAuthorID);
        pstmt->setInt(2, paper.confID);
        pstmt->setString(3, paper.confKeyword);
        pstmt->setString(4, paper.title);
        pstmt->setString(5, paper.abstract);
        pstmt->setString(6, pdf);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Store paperID
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperID);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int paperID = rs->getInt(1);

	if( paperID == 0)
		return;

        delete rs;
        delete pstmt;

        // =======================================
        // Paper Authors
        pstmt = dbcon->prepareStatement(insertAuthors);

	std::vector<PersonalInfo>::const_iterator it;
	for (it = paper.authors.begin(); it != paper.authors.end(); it ++)
	{
		PersonalInfo pInfo = *it;	

		pstmt->setInt(1, paperID);
		pstmt->setInt(2, pInfo.infoID);

	        pstmt->executeUpdate();
	}
	delete pstmt;

        // =======================================
        // Keywords
      	if (paper.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertKeywords);
		    std::vector<std::string>::const_iterator it;
      		for (it = paper.keywords.begin(); it != paper.keywords.end(); it ++)
		    {
		    	std::string word = *it;	

            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	
		    	pstmt->setInt(1, paperID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;

      	}

}

void Database::updatePaper(Paper paper) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* updatePaper = "UPDATE Paper SET leadAuthorID=?, confID=?, keywordID=(SELECT keywordID FROM Keywords WHERE keyword=?), paperTitle=?, paperAbstract=? WHERE paperID=?";
        const char* deleteAuthors = "DELETE FROM paperAuthors WHERE paperID=?";
	const char* insertAuthors = "INSERT IGNORE INTO paperAuthors(paperID, authorID) VALUES(?, ?)";

        const char* deleteKeywords = "DELETE FROM PaperKeywords WHERE paperID=?";
	const char* insertKeywords = "INSERT IGNORE INTO PaperKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Paper
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(updatePaper);
        pstmt->setInt(1, paper.leadAuthorID);
        pstmt->setInt(2, paper.confID);
        pstmt->setString(3, paper.confKeyword);
        pstmt->setString(4, paper.title);
        pstmt->setString(5, paper.abstract);
        pstmt->setInt(6, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Authors Delete
        pstmt = dbcon->prepareStatement(deleteAuthors);
        pstmt->setInt(1, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Paper Authors
        pstmt = dbcon->prepareStatement(insertAuthors);

	std::vector<PersonalInfo>::const_iterator it;
	for (it = paper.authors.begin(); it != paper.authors.end(); it ++)
	{
		PersonalInfo pInfo = *it;	

		pstmt->setInt(1, paper.paperID);
		pstmt->setInt(2, pInfo.infoID);

	        pstmt->executeUpdate();
	}
	delete pstmt;

        // =======================================
        // Keywords Delete
        pstmt = dbcon->prepareStatement(deleteKeywords);
        pstmt->setInt(1, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Keywords Insert
      	if (paper.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertKeywords);
		    std::vector<std::string>::const_iterator it;
      		for (it = paper.keywords.begin(); it != paper.keywords.end(); it ++)
		    {
		    	std::string word = *it;	
            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	pstmt->setInt(1, paper.paperID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;
      	}
}

void Database::addPaperAccepted(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertAccepted = "INSERT INTO AcceptedPapers VALUES(?, ?)";

        // =======================================
        // Paper Accepted
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertAccepted);
        pstmt->setInt(1, confID);
        pstmt->setInt(2, paperID);

        pstmt->executeUpdate();

	delete pstmt;
}

std::vector<int> Database::fetchPaperAccepted(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getAccepted = "SELECT paperID FROM AcceptedPapers WHERE confID=?";

        // =======================================
        // Paper Accepted
	std::vector<int> vec;

        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;

	pstmt = dbcon->prepareStatement(getAccepted);
        pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

	delete pstmt;
	delete rs;
}

Review Database::fetchReview(int paperID, int reviewerID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReview = "SELECT * FROM Review WHERE (paperID=? and reviewerID=? and confID=?)";
        // =======================================
        // Review
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReview);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, reviewerID);
	pstmt->setInt(3, confID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return Review();
	}

        int reportID = rs->getInt(1);
        int overall = rs->getInt(5);
        int confidence = rs->getInt(6);
        int relevance = rs->getInt(7);
        int originality = rs->getInt(8);
        int significance = rs->getInt(9);
        int presentation = rs->getInt(10);
        int techQuality = rs->getInt(11);
        int evaluation = rs->getInt(12);
        std::string commentsStrength = rs->getString(13);
        std::string commentsWeakness = rs->getString(14);
        std::string commentsSuggestions = rs->getString(15);
        std::string commentsShortPaper = rs->getString(16);
        std::string commentsBestAward = rs->getString(17);

	Review review(reportID,
		paperID, 
		reviewerID, 
		overall, 
		confidence, 
		relevance, 
		originality, 
		significance, 
		presentation, 
		techQuality, 
		evaluation, 
		commentsStrength, 
		commentsWeakness, 
		commentsSuggestions, 
		commentsShortPaper, 
		commentsBestAward);

        delete rs;
        delete pstmt;

	return review;
}

void Database::modifyReview(Review review, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertReview = "INSERT INTO Review(paperID, reviewerID, confID, overall, confidence, relevance, originality, significance, presentation, techQuality, evaluation, commentsStrength, commentsWeakness, commentsSuggestions, commentsShortPaper, commentsBestAward) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"; 
	const char* updateReview = "UPDATE Review SET paperID=?, reviewerID=?, confID=?, overall=?, confidence=?, relevance=?, originality=?, significance=?, presentation=?, techQuality=?, evaluation=?, commentsStrength=?, commentsWeakness=?, commentsSuggestions=?, commentsShortPaper=?, commentsBestAward=? WHERE reportID=?"; 
        // =======================================
        // Reviews
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertReview);

	if (review.reportID==0)
	{
		pstmt = dbcon->prepareStatement(insertReview);

		pstmt->setInt(1, review.paperID);
		pstmt->setInt(2, review.reviewerID);
		pstmt->setInt(3, confID);
		pstmt->setInt(4, review.overall);
		pstmt->setInt(5, review.confidence);
		pstmt->setInt(6, review.relevance);
		pstmt->setInt(7, review.originality);
		pstmt->setInt(8, review.significance);
		pstmt->setInt(9, review.presentation);
		pstmt->setInt(10, review.techQuality);
		pstmt->setInt(11, review.evaluation);
		pstmt->setString(12, review.commentsStrength);
		pstmt->setString(13, review.commentsWeakness);
		pstmt->setString(14, review.commentsSuggestions);
		pstmt->setString(15, review.commentsShortPaper);
		pstmt->setString(16, review.commentsBestAward);

		pstmt->executeUpdate();
	}
	else
	{
		pstmt = dbcon->prepareStatement(updateReview);

		pstmt->setInt(1, review.paperID);
		pstmt->setInt(2, review.reviewerID);
		pstmt->setInt(3, confID);
		pstmt->setInt(4, review.overall);
		pstmt->setInt(5, review.confidence);
		pstmt->setInt(6, review.relevance);
		pstmt->setInt(7, review.originality);
		pstmt->setInt(8, review.significance);
		pstmt->setInt(9, review.presentation);
		pstmt->setInt(10, review.techQuality);
		pstmt->setInt(11, review.evaluation);
		pstmt->setString(12, review.commentsStrength);
		pstmt->setString(13, review.commentsWeakness);
		pstmt->setString(14, review.commentsSuggestions);
		pstmt->setString(15, review.commentsShortPaper);
		pstmt->setString(16, review.commentsBestAward);
		pstmt->setInt(17, review.reportID);

		pstmt->executeUpdate();
	}
	delete pstmt;
}

Discussion Database::fetchDiscussion(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getDiscussion = "SELECT comment, reviewerID, commentID FROM ReviewerDiscussion WHERE (paperID=? and confID=?)";
        // =======================================
        // Discussion
        std::list<DiscussionPost> discussion;
	
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;

	pstmt = dbcon->prepareStatement(getDiscussion);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		std::string comment = rs->getString(1);
		int reviewerID = rs->getInt(2);
		int commentID = rs->getInt(3);
		DiscussionPost discuss(comment, reviewerID, commentID);
                discussion.push_back(discuss);
        }

        delete rs;
        delete pstmt;
}

DiscussionPost Database::fetchRebuttal(int paperID, int userID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getDiscussionPost = "SELECT comment, reviewerID, commentID FROM ReviewerDiscussion WHERE (paperID=? and reviewerID=? and confID=?)";

        // =======================================
        // Discussion Post
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getDiscussionPost);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, userID);
	pstmt->setInt(3, confID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return DiscussionPost();
	}

	std::string comment = rs->getString(1);
	int reviewerID = rs->getInt(2);
	int commentID = rs->getInt(3);
	DiscussionPost discuss(comment, reviewerID, commentID);

        delete rs;
        delete pstmt;
	
	return discuss;
}

void Database::createDiscussionPost(DiscussionPost discussionPost, int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertDiscussPost = "INSERT INTO ReviewerDiscussion(paperID, confID, reviewerID, comment) VALUES(?, ?, ?, ?)";
        // =======================================
        // Discussion
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertDiscussPost);
	
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);
	pstmt->setInt(3, discussionPost.reviewerID);
	pstmt->setString(4, discussionPost.comment);

	pstmt->executeUpdate();

	delete pstmt;
}

std::vector<int> Database::getAuthorsForPaper(int paperID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getAuthors = "SELECT authorID FROM paperAuthors WHERE paperID=?";

        // =======================================
        // Authors
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getAuthors);
	pstmt->setInt(1, paperID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int authorID = rs->getInt(1);
                vec.push_back(authorID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::string Database::getOrganisationForAuthor(int infoID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getOrg = "SELECT organisation FROM PersonalInfo WHERE infoID=?";

        // =======================================
        // Org
	std::vector<std::string> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getOrg);
	pstmt->setInt(1, infoID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return std::string();
	}

	std::string org = rs->getString(1);

    delete rs;
    delete pstmt;
	
	return org;
}

std::vector<int> Database::getReviewersForOrganisation(std::string org) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewers = "SELECT userID FROM UserType WHERE (userType = 'pc' and userID IN (SELECT userID FROM PersonalInfo WHERE (userID IS NOT NULL and organisation=?)))";

        // =======================================
        // Reviewers
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewers);
	pstmt->setString(1, org);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int reviewerID = rs->getInt(1);
                vec.push_back(reviewerID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::vector<int> Database::getPapersForAuthor(int authorID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPapers = "SELECT paperID FROM paperAuthors WHERE authorID=?";

        // =======================================
        // Papers
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPapers);
	pstmt->setInt(1, authorID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::vector<std::string> Database::getKeywordsForPaper(int paperID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT keywordID FROM PaperKeywords WHERE paperID=?)";

        // =======================================
        // Paper Keywords
        std::vector<std::string> keywords;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperKeywords);
	pstmt->setInt(1, paperID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                keywords.push_back(keyword);
        }

        delete rs;
        delete pstmt;

	return keywords;
}

std::vector<std::string> Database::getKeywordsForUser(int userID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getUserKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT expertiseID FROM ExpertiseArea WHERE userID=?)";

        // =======================================
        // Expertise Keywords
        std::vector<std::string> keywords;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserKeywords);
	pstmt->setInt(1, userID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                keywords.push_back(keyword);
        }

        delete rs;
        delete pstmt;

	return keywords;
}

std::vector<int> Database::getReviewersForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewers = "SELECT userID FROM UserType WHERE (userType='pc' and confID=?)";

        // =======================================
        // Reviewers
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewers);
	pstmt->setInt(1, confID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                int userID = rs->getInt(1);
                vec.push_back(userID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

int Database::getReviewerPreference(int userID, int confID, int paperID) throw (const char*)
{
	const char* getReviewerPreference = "SELECT preference FROM ReviewerPreference WHERE (userID=? and confID=? and paperID=?)";

        // =======================================
        // Reviewer Preference
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewerPreference);
	pstmt->setInt(1, userID);
	pstmt->setInt(2, confID);
	pstmt->setInt(3, paperID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return -1;
	}

    	int preference = rs->getInt(1);

        delete rs;
        delete pstmt;
	
	return preference;
}

void Database::assignPaper(int paperID, int reviewerID, int confID) throw (const char*)
{
    if (invalid)
            throw (noDB);

	const char* insertPaperAssigned = "INSERT INTO PaperAssigned(paperID, reviewerID, confID) VALUES(?, ?, ?)";

    // =======================================
    // Paper Assigned
    sql::PreparedStatement *pstmt = NULL;
    pstmt = dbcon->prepareStatement(insertPaperAssigned);
    pstmt->setInt(1, paperID);
    pstmt->setInt(2, reviewerID);
    pstmt->setInt(3, confID);

    pstmt->executeUpdate();

    delete pstmt;
}

std::vector<int> Database::fetchReviewersAssigned(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewersIDs = "SELECT reviewerID FROM PaperAssigned WHERE (paperID=? and confID=?)";

        // =======================================
        // Reviewer ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewersIDs);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int reviewerID = rs->getInt(1);
                vec.push_back(reviewerID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM Paper WHERE confID=?";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForAllocatedReviewer(int reviewerID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM PaperAssigned WHERE (reviewerID=? and confID)";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, reviewerID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForLeadAuthor(int leadAuthorID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM Paper WHERE (leadAuthorID=? and confID=?)";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, leadAuthorID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getUserIDsForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getUserIDs = "SELECT userID FROM UserType WHERE confID=?";

        // =======================================
        // User ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserIDs);
	pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}


void Database::adminChangeUserName(std::string currentUN, std::string newUN) throw (const char*)
{
	const char* getUserID = "SELECT userID FROM UserAccount WHERE username = ?";
        const char* updateUserName = "UPDATE UserAccount SET username = ? WHERE userID=?";

        // =======================================
        // Store userID
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserID);
        pstmt->setString(1, currentUN);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int userID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Personal Info Update

        pstmt = dbcon->prepareStatement(updateUserName);
        pstmt->setString(1, newUN);
        pstmt->setInt(2, userID);

        pstmt->executeUpdate();

        delete pstmt;
}

void Database::adminChangePassword(std::string username, std::string password) throw (const char*)
{
        const char* updatePassword = "UPDATE UserAccount SET password = ? WHERE username=?";

        // =======================================
        // Personal Info Update
        sql::PreparedStatement *pstmt = NULL;

        pstmt = dbcon->prepareStatement(updatePassword);
        pstmt->setString(1, password);
        pstmt->setString(2, username);

        pstmt->executeUpdate();

        delete pstmt;
}

UserType_t Database::adminFetchUserType(std::string username, std::string confTitle) throw (const char*)
{
//    const char* 
    std::string fetchUserType = "SELECT userType FROM UserType WHERE (userID=(SELECT userID FROM UserAccount WHERE username=?) and confID=(SELECT confID FROM Conference WHERE name=?))";
    
    // ============================================
    // User Type Update
    UserType_t userType;
    sql::PreparedStatement *pstmt = NULL;
    sql::ResultSet *rs = NULL;
    
    pstmt = dbcon->prepareStatement(fetchUserType.c_str());
    pstmt->setString(1, username);
    pstmt->setString(2, confTitle);
    
    rs = pstmt->executeQuery();
    bool haveRecord = rs->next();
    if (!haveRecord)
    {
        userType = NOUSER;
    }
    else
    {
        int e = rs->getInt(1);           
        if (e = 1)
            userType = AUTHOR;
        else if (e = 2)
            userType = REVIEWER;
        else if (e = 3)
            userType = PCCHAIR;
    }

    delete pstmt;
    delete rs;
    
    return userType;
}

void Database::adminChangeUserType(std::string username, std::string confTitle, UserType_t userType) throw (const char*)
{
    switch(userType)
    {
        case AUTHOR:
            setUserAsAuthorByNames(username, confTitle);
            break;
        case REVIEWER:
            setUserAsChairByNames(username, confTitle);
            break;
        case PCCHAIR:
            setUserAsPCByNames(username, confTitle);
            break;
    }
}
