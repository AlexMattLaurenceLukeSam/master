#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "MyRecord.h"
#include "MyRecordStore.h"

#include "Database.hpp"
#include "../Server/User.hpp"

#include <vector>

typedef User* userPtr;
std::vector<userPtr> g_theUsers;

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
                userPtr ptr = (*it);
                std::string key = ptr->userName;
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
        userPtr next;
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
		next = new User(
			username,
			name,
			email,
			organisation,
			phone,
			password,
			keywords);

                g_theUsers.push_back(next);
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
		next = new User(
			username,
			name,
			email,
			organisation,
			phone,
			password,
			keywords);

                g_theUsers.push_back(next);
        }
}
