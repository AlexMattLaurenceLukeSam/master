#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "MyRecord.h"
#include "MyRecordStore.h"

#include "Database.hpp"
#include "../Server/User.hpp"

#include <vector>

std::vector<User> g_theUsers;

static void createUsers();

int main(int arc, char *argv[])
{
        createUsers();
        Database db;
        if (!db.isOK())
        {
                std::cout << "Failed to open database file" << std::endl;
                exit(1);
        }
/*std::vector<std::string> keywords;
username = "tom";
password = "fake";
name = "Thomas";
email = "boos_tom@ourcompany.com.au";
organisation = "University of Wollongong";
phone = "04666666666";
keywords.push_back("mathematics");
keywords.push_back("science");
User usertemp(
username,
name,
email,
organisation,
phone,
password,
keywords);*/
User usertemp("foo",
"bar",
"thefoo",
"boos_tom@ourcompany.com.au",
"University of Wollongong",
"04666666666",
std::vector<std::string>{"mathematics","science"});
std::string key = usertemp.userName;
db.putUser(key, usertemp);

Conference conferencetemp(true, 
"baz",
"blah",
"boo",
"flop",
std::vector<std::string>("one", "two"),
TRUE,
Date(1,12,30),
TRUE,
Date(1,12,30),
TRUE,
Date(1,12,30),
TRUE,
Date(1,12,30),
TRUE,
Date(1,12,30),
4,
250);
std::string title = conferencetemp.title;
db.putConf(title, conferencetemp);

PersonalInfo infotemp("a", "b", "c", "d");

const int CONFID = 7;
Paper papertemp(5,
CONFID,
"fee",
"fi",
std::vector<PersonalInfo>(infotemp),
std::vector<std::string>("fo", "fum"),
"giants");
std::string pdf = "whyyougoanddothesethings";
db.createPaper(papertemp, pdf);

/* User usertemp2("dick",
"wrong",
"Dick",
"clever_dick@ourcompany.com.au",
"University of Wollongong",
"04666667666",
std::vector<std::string>{"geographyt","english"});
std::vector theUsers{usertemp, usertemp2}; */

        std::vector<User>::const_iterator it;
        for(it=g_theUsers.begin(); it!=g_theUsers.end(); it++)
        {
                User ptr = *it;
                std::string key = ptr.userName;
                db.putUser(key, ptr);
                std::cout << "Wrote record " << key << std::endl;
        }

	std::vector<std::string> Names = db.allUserNames();
	std::vector<std::string>::iterator iter;

        for(iter=Names.begin(); iter!=Names.end(); iter++)
        {
                std::string key = (*iter);
                User user = db.fetchUser(key);
                std::cout << user.userName << " " << user.name << " " <<  user.keywords[0] << " " << user.email << " " << key << std::endl;
        }
        
        std::vector<int> ConfIDs{db.activeConfIDs()};
        std::vector<int>::iterator confiter;
        for(confiter=ConfIDs.begin(); confiter!=ConfIDs.end(); confiter++)
        {
        	int key = (*iter);
        	Conference conference = db.fetchConference(key);
        	std::cout << conference.title << " " << conference.keywords[0] << std::endl;
        }
        
        std::vector<int> PaperIDs{db.getPaperIDsForConf(CONFID)};
        std::vector<int>::iterator paperiter;
        for(paperiter=PaperIDs.begin(); paperiter!=PaperIDs.end(); paperiter++)
        {
        	int key = (*iter);
        	Paper paper = db.fetchPaper(key);
        	std::cout << paper.paperID << " " << paper.confID << " " << paper.leadAuthorID << " " << paper.keywords[0] << std::endl;
        }
//        for(it=g_theUsers.begin(); it!=g_theUsers.end(); it++)
//        {
//                userPtr ptr = (*it);
//                int key = ptr->userID;
//                db.deleteRecord(key);
//                std::cout << "Deleted record " << key << std::endl;
//        }
        return EXIT_SUCCESS;
}

static void createUsers()
{
        // Hard code procedural creation of a few records so that can
        // have some data to show in the Qt based GUI
        std::string username;
        std::string password;
        std::string name;
        std::string email;
        std::string organisation;
	std::string phone;

        // You will need to adjust filenames etc to match the image files
        // that you provide
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
