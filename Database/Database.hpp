#include <string>
#include <vector>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "MyRecord.h"

class DataBase {
public:
        Database();

        ~Database();

	// CSCI222

	User *fetchUser(const char*key) throw (const char*);


        // Delete - returns false if there wasn't a record with that key
        bool deleteRecord(const char* key) throw (const char*);
        // Exists - is there a record with a given key
        bool exists(const char* key) throw (const char*);
        // Put - insert/replace a record; returns false if failed
        // (In this example, key is actually the same as name field in data record)
        void put(const char* key, const MyRecord *data) throw (const char*);
        // Get - get record with keyerror: Failed connect to github.com:443; Connection refused while accessing
        MyRecord *get(const char*key) throw (const char*);

        std::vector<MyRecord*> *getInRole(const char* role) throw (const char*);

        void close();

        std::vector<std::string> *allKeys();

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

        void recordToTables(const MyRecord *data);

};
