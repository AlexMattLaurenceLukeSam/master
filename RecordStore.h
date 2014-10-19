#include <string>
#include <vector>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "MyRecord.h"

class MyRecordStore {
public:
        MyRecordStore();

        ~MyRecordStore();
        // Delete - returns false if there wasn't a record with that key
        bool deleteRecord(const char* key) throw (const char*);
        // Exists - is there a record with a given key
        bool exists(const char* key) throw (const char*);
        // Put - insert/replace a record; returns false if failed
        // (In this example, key is actually the same as name field in data record)
        void put(const char* key, const MyRecord *data) throw (const char*);
        // Get - get record with keyerror: Failed connect to github.com:443; Connection refused while accessing
        MyRecord *get(const char*key) throw (const char*);

        vector<MyRecord*> *getInRole(const char* role) throw (const char*);

        void close();

        std::vector<std::string> *allKeys();

        bool isOK()
        {
                return !(this->invalid);
        }

private:
        bool invalid;
        const char* *dbcon;
        sql::Connection *dbcon;
        sql::Drive *driver;
        MyRecordStore(const MyRecordStore& orig);
        MyRecordStore& operator=(const MyRecordStore);

        void recordToTables(const MyRecord *data);

};
