#include <string>
#include <vector>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "MyRecord.h"
#include "../Server/User.hpp"
#include "../Server/Conference.hpp"

class Database {
public:
        Database();

        ~Database();

        void close();

	// USER
	User *fetchUser(std::string key) throw (const char*);
        bool existsUserName(std::string key) throw (const char*);
        void putUser(std::string key, const User *user) throw (const char*);
        std::vector<int> *allUserIDs();
        std::vector<std::string> *allUserNames();

	// KEYWORD
        bool existsKeyword(std::string key) throw (const char*);
	void addKeyword(std::string key) throw (const char*);

	// CONFERENCE
	Conference *fetchConference(int key) throw (const char*);


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
        void createUser(const User *user);
        void updateUser(const User *user);

};
