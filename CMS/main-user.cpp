/*
 * File:   main.cpp
 * Author: ubuntu
 *
 * Created on 29 October 2014, 6:13 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <QApplication>

#include "Database.hpp"
#include "User.hpp"
#include "Conference.hpp"
#include "Paper.hpp"
#include "Algo.hpp"
#include "MainWindow.hpp"

#include <vector>

std::vector<User> g_theUsers;
std::vector<Conference> g_theConfs;
std::vector<Paper> g_thePapers;

//static void createUsers();
//static void createConf();
//static void createPaper();

int main(int argc, char *argv[])
{
//    createUsers();
//    createConf();
//    createPaper();
    
    QApplication app(argc, argv);
    
    Database db;

    if (!db.isOK())
    {
            std::cout << "Failed to open database file" << std::endl;
            exit(EXIT_FAILURE);
    }
    
    MainWindow mWindow(&db);
    mWindow.show();
    
    int rtnVal = app.exec();
/*
    std::vector<User>::const_iterator it;
    for(it=g_theUsers.begin(); it!=g_theUsers.end(); it++)
    {
            User ptr = *it;
            std::string key = ptr.userName;
            db.putUser(key, ptr);
            std::cout << "Wrote user: " << key << std::endl;
    }

    std::vector<Conference>::const_iterator it2;
    for(it2=g_theConfs.begin(); it2!=g_theConfs.end(); it2++)
    {
        Conference ptr = *it2;
        std::string key = ptr.title;
	    db.putConf(key, ptr);
        std::cout << "Wrote conference: " << key << std::endl;
    }

    std::vector<Paper>::const_iterator it3;
    for(it3=g_thePapers.begin(); it3!=g_thePapers.end(); it3++)
    {
        Paper ptr = *it3;
	    std::string pdf = "whyyougoanddothesethings";
	    if(!db.existsPaperTitleConf(ptr))
	    {
	    	db.createPaper(ptr, pdf);
           	std::cout << "Wrote paper: " << ptr.title << std::endl;
	    }
    }

	std::vector<std::string> Names = db.allUserNames();
	std::vector<std::string>::iterator iter;

    for(iter=Names.begin(); iter!=Names.end(); iter++)
    {
        std::string key = (*iter);
        User user = db.fetchUser(key);
        std::cout << "fetch username: " << user.userName << " name: " << user.name << " first expertise: " <<  user.keywords[0] << " email: " << user.email << std::endl;
    }
    
    std::vector<int> ConfIDs = db.activeConfIDs();
    std::vector<int>::iterator confiter;
    for(confiter=ConfIDs.begin(); confiter!=ConfIDs.end(); confiter++)
    {
    	int key = (*confiter);
    	Conference conference = db.fetchConference(key);
    	std::cout << "fetch conference: " << conference.title << " first keyword: " << conference.keywords[0] << std::endl;
    }
    
    std::vector<int> PaperIDs(db.getPaperIDsForConf(1));
    std::vector<int>::iterator paperiter;
    for(paperiter=PaperIDs.begin(); paperiter!=PaperIDs.end(); paperiter++)
    {
    	int key = (*paperiter);
    	Paper paper = db.fetchPaper(key);
    	std::cout << "fetch paper " << "paperID:" << paper.paperID << " confID:" << paper.confID << " leadAuthorID:" << paper.leadAuthorID << " first keyword: " << paper.keywords[0] << std::endl;
    }
*/
    int PFR = 1;
    PaperForReview pfr(PFR, PFR, PFR, &db);

    return rtnVal;
}
/*
static void createUsers()
{
    std::string username;
    std::string password;
    std::string name;
    std::string email;
    std::string organisation;
	std::string phone;
    {
	    std::vector<std::string> keywords;
        username = "tom";
	    password = "fake";
        name = "Thomas";
        email = "boos_tom@ourcompany.com.au";
	    organisation = "University of Wollongong";
        phone = "04666666666";
	    keywords.push_back("mathematics");
	    keywords.push_back("science");
	    User user(
	    	username,
	    	name,
	    	email,
	    	organisation,
	    	phone,
	    	password,
	    	keywords);

        g_theUsers.push_back(user);
    }
    {
	    std::vector<std::string> keywords;
        username = "dick";
	    password = "wrong";
        name = "Dick";
        email = "clever_dick@ourcompany.com.au";
        email = "boos_m@ourcompany.com.au";
	    organisation = "University of Wollongong";
        phone = "04666667666";
	    keywords.push_back("geographyt");
	    keywords.push_back("english");
	    User user(
	    	username,
	    	name,
	    	email,
	    	organisation,
	    	phone,
	    	password,
	    	keywords);

        g_theUsers.push_back(user);
    }
}

static void createConf()
{
	bool active = true;
	std::string title = "maths conference";
	std::string topic = "linear algebra";
	std::string description = "exciting LA and MORE!!";
	std::string location = "UoW";
	std::vector<std::string> keywords;
	keywords.push_back("maths");
	keywords.push_back("linear algebra");
	Date date(1,12,30);
	bool open = true;
	int reviewersPerPaper = 10;
	int postWordLimit = 250;
	Conference conferencetemp(
		active,
		title,
		topic,
		description,
		location,
		keywords,
		open,
		date,
		open,
		date,
		open,
		date,
		open,
		date,
		open,
		date,
		reviewersPerPaper,
		postWordLimit);
	
    g_theConfs.push_back(conferencetemp);
}

static void createPaper()
{
	PersonalInfo infotemp(
        "Dick",
        "clever_dick@ourcompany.com.au",
		"University of Wollongong",
        "04666667666",
		2);
	
	std::vector<PersonalInfo> authors;
	authors.push_back(infotemp);
	std::vector<std::string> keywords;
	keywords.push_back("linear algebra");
	std::string title("LA");
	std::string abstract("amazing!");
	std::string confKeyword("linear algebra");
	int CONFID = 1;
	int leadAuthorID = 2;

	Paper papertemp(
	CONFID,
	leadAuthorID,
	title,
	abstract,
	authors,
	keywords,
	confKeyword);

    g_thePapers.push_back(papertemp);
}
*/
