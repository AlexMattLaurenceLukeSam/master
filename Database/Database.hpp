#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "MyRecord.h"
#include "../Server/User.hpp"
#include "../DataAll/Conference.hpp"
#include "../DataAll/Date.hpp"
#include "../DataAll/PersonalInfo.hpp"
#include "../DataAll/Paper.hpp"
#include "../DataAll/PaperSummary.hpp"
#include "../DataAll/Review.hpp"
#include "../DataAll/Discussion.hpp"
#include "../DataAll/DiscussionPost.hpp"

class Database {
public:
        Database();

        ~Database();

        void close();

	// USER
	User fetchUser(std::string key) throw (const char*);
        bool existsUserName(std::string key) throw (const char*);
        void putUser(std::string key, User *user) throw (const char*);
        std::vector<int> allUserIDs();
        std::vector<std::string> allUserNames();

	// KEYWORD
        bool existsKeyword(std::string key) throw (const char*);
	void addKeyword(std::string key) throw (const char*);

	// CONFERENCE
	Conference fetchConference(int key) throw (const char*);
        bool existsConfName(std::string key) throw (const char*);
        void putConf(std::string key, Conference *conf) throw (const char*);
        std::vector<int> allConfIDs();
        std::vector<std::string> allConfNames();
        std::vector<int> activeConfIDs();
        std::vector<std::string> activeConfNames();

	// PAPER
	PaperSummary fetchPaperSummary(int key) throw (const char*);
        std::vector<PaperSummary> allAuthorsPaperSummary(int confID, int authorID) throw (const char*);
        Paper fetchPaper(int key) throw (const char*);
        void createPaper(Paper *paper, std::string pdf);

	// ALGO
	std::vector<int> getAuthorsForPaper(int paperID) throw (const char*);
	std::vector<std::string> getOrganisationForAuthor(int infoID) throw (const char*);
	std::vector<int> getReviewersForOrganisation(std::string org) throw (const char*);
	std::vector<int> getPapersForAuthor(int authorID) throw (const char*);
	std::vector<std::string> getKeywordsForPaper(int paperID) throw (const char*);
	std::vector<std::string> getKeywordsForUser(int userID) throw (const char*);
	std::vector<int> getReviewersForConf(int confID) throw (const char*);
	int getReviewerPreference(int userID, int confID, int paperID) throw (const char*);
	
	std::vector<int> getPaperIDsForConf(int confID) throw (const char*);	
	std::vector<int> getPaperIDsForAllocatedReviewer(int reviewerID, int confID) throw (const char*);
	
//        // Delete - returns false if there wasn't a record with that key
//        bool deleteRecord(const char* key) throw (const char*);
//        // Put - insert/replace a record; returns false if failed
//        // (In this example, key is actually the same as name field in data record)
//        void put(const char* key, const MyRecord *data) throw (const char*);
//        // Get - get record with keyerror: Failed connect to github.com:443; Connection refused while accessing
//        MyRecord *get(const char*key) throw (const char*);
//
//        std::vector<MyRecord*> *getInRole(const char* role) throw (const char*);
//
//

        bool isOK()
        {
                return !(this->invalid);
        }

private:
        bool invalid;
        const char* dbname;
        sql::Connection *dbcon;
        sql::Driver *driver;
        Database(const Database& orig);
        Database& operator=(const Database);

//        void recordToTables(const MyRecord *data);

	// USER
        void createUser(User *user);
        void updateUser(User *user);

	// CONF
        void createConf(Conference *conf);
        void updateConf(Conference *conf);

};
#endif
