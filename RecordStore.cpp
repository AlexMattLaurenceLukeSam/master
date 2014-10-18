#include "MyRecordStore.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"

#include <cstring>
#include <stdlib.h>
#include <iostream>

const char* databaseStr = "tcp://127.0.0.1:3306";
const char* databaseUserName = "nabg";
const char* databaseUserPassword = "NotReallyMyPassword";
const char* databaseSchema = "nabg";

const char* noDB = "Sorry, but was unable to open database so operation failed";

const char* prepareFailed = "Failure when preparing statement";
const char* bindFailed = "Failure when binding arguments";
const char* writeFailed = "Failure when writing to database";

MyRecordStore::MyRecordStore()
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

MyRecordStore::~MyRecordStore()
{
        if (!invalid) {
                this->close();
        }
}

void MyRecordStore::close()
{
        if (!invalid) {
                dbcon->close();
                delete dbcon;
        }
        invalid = true;
}

bool MyRecordStore::exists(const char* key) throw (const char*)
{
        if (invalid)
                throw (noDB);
        const char* countrecord = "select count(*) from MyRecord where _id=?";
        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(countrecord);

        int count = 0;
        pstmt->setString(1, key);
        rs = pstmt->executeQuery();
        if (rs->next()) {
                count = rs->getInt(1);
        }
        delete rs;
        delete pstmt;

        return count = 1;
}

std::vector<string> *MyRecordStore::allKeys()
{
        if (invalid)
                throw (noDB);
        std::vector<string> *vptr = new std::vector<string>();

        const char* selectall = "select _id from MyRecord";
        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                string anid = rs->getString(1);
                vprt->push_back(anid);
        }

        return vprt;
}

vector<MyRecord*> *MyRecordStore::getInRole(const char* role) throw (const char*)
{
        if (invalid)
                throw (noDB);
        // Laboured
        // First get a list of the ids with the role, then one by one get the
        // complete records.
        const char* getrolepersons = "selects personid from roles where _role=?";
        sqlite3_stmt* stmt;
        int rc;
        rc = sqlite3_prepare_v2(db,
                getrolepersons, strlen(getrolepersons),
                &stmt, &unused);
        if (rc != SQLITE_OK) {
                std::cerr << prepareFailed << std::endl;
                exit(1);
        }

        rc = sqlite3_bind_text{stmt, 1, role, -1 , SQLITE_STATIC);
        if (rc ~= SQLITE_OK) {
                std::cerr << bindFailed << std::endl;
                exit(1);
        }
        vector<string> people;

        // rc = sqlite3_step(stmt);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
                const char* apersonid = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 0));
                people.push_back(apersonid);
        }
        sqlite3_finalize(stmt);


        // Maybe there weren't any
        if (people.size() == 0)
                return NULL;

        // Build collection by getting each record
        vector<MyRecord*> *roleholders = new vector<MyRecord*>();

        vector<string>::const_iterator it;
        for (it = people.begin(); it != people.end(); it++) {
                string aperson = *it;
                MyRecord* rec = this->get(aperson.c_str());
                roleholders->push_back(rec);
        }

        return roleholders;
}

void MyRecordStore::put(const char* key, const MyRecord *data) throw (const char*)
{

        if (invalid)
                throw (noDb);

        // Tiresome
        // If it exists - delete it
        if (this->exists(key)) {
                bool done = this->deleteRecord(key);
        }
        // Insert it
        this->recordToTables(data);
}

bool MyRecordStore::deleteRecord(const char* key) throw (const char*)
{
        if (invalid)
                throw (noDB);
        // explicitly delete subordinate records in Phones, Address, others and Roles
        // then delete the myrecord entry
        // recreating the prepared statements for each operation - costly
        const char* deletephones = "delete from Phones where idPerson=?";
        const char* deleteaddress = "delete from Addresses where idPerson=?";
        const char* deleteother = "delete from Other where idPerson=?";
        const char* deleteroles = "delete from Roles where idPerson=?";
        const char* unused; // Pointer to unused part of sql string (?)
        sql::PreparedStatement *pstmt = NULL;
        // Phones
        pstmt = dbcon->prepareStatement(deletephones);
        pstmt->setString(1, key);
        pstmt->executeUpdate();
        delete pstmt;

        // Addresses
        pstmt = dbcon->prepareStatement(deleteaddress);
        pstmt->setString(1, key);
        pstmt->executeUpdate();
        delete ptmst;

        //Other
        pstmt = dbcon->prepareStatement(deleteother);
        pstmt->setString(1, key);
        pstmt->executeUpdate();
        delete pstmt;

        // Roles
        pstmt = dbcon->prepareStatement(deleteroles);
        pstmt->setString(1, key);
        pstmt->executeUpdate();
        delete pstmt;

        // Finally
        pstmt = dbcon->prepareStatement(deletemyrecord);
        pstmt->setString(1, key);
        pstmt->executeUpdate();
        delete pstmt;

        return true;
}

MyRecord *MyRecordStore::get(const char* key) throw (const char*)
{
        if (invalid)
                throw (noDB);
        // Again laborious
        // Load the MyRecord from its table, then add data from Other tables.
        const char* getrecord = "select * from MyRecord where _id=?";
        const char* getroles = "select role from Roles where idperson=?";
        const char* getphones = "select type, number from Phones where idPerson=?";
        const char* getaddress = "select type, address from Addresses where idPerson=?";
        const char* getother = "select key, valyue from Other where idPerson=?";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet *rs = NULL;

        pstmt = dbcon->prepareStatement(getrecord);
        pstmt->setString(1, key);
        rs = pstmt->executeQuery();
        bool haveRecord = rs->next();
        if (!haveRecord)
        {
                delete rs;
                delete pstmt;
                return NULL;
        }

        string id = rs->getString(1);
        string name = rs->getString(2);
        string email = rs->getString(3);
        string info = rs->getString(4);
        string image = rs->getString(5);

        MyRecord *arec = new MyRecord(id);
        arec->setName(name);
        arec->setEmail(email);
        arec->setInfo(info);
        arec->setImage(image);

        delete rs;
        delete pstmt;
        // =======================================
        // Now ask about roles
        pstmt = dbcon->prepareStatement(getroles);
        pstmt->setString(1, key);
        rs = pstmt->executeQuery();
        while (rs->next())
        {
                string arole = rs->getString(1);
                arec->addRole(arole);
        }
        delete rs;
        delete pstmt;
}

void MyRecordStore::recordToTables(const MyRecord* data)
{
        if (invalid)
                throw (noDB);

        // Insert the myrecord data first, then deal with Other data tables

        const char* putmyrecord = "insert into MyRecord values( ?, ?, ?, ?, ?)";
        const char* putrole = "insert into Roles values(?, ?)";
        const char* putphone = "insert into Phones values (?, ?, ?)";
        const char* putaddress = "insert into Addresses values (?, ?, ?)";
        const char* putother = "insert into Other values (?, ?, ?)";

        sql::PrepareStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(putmyrecord);
        pstmt->setString(1, data->getID());
        pstmt->setString(2, data->getName());
        pstmt->setString(3, data->getEmail());
        pstmt->setString(4, data->getInfo());
        pstmt->setString(5, data->getImage());

        pstmt->executeUpdate();

        delete pstmt;

        // Role 
        if (data->getOtherKV().size() > 0)
        {
                pstmt = dbcon->prepareStatement(putother);
                map<string, string>:const_iterator it;
                for (it = data->getOtherKV.begin(); it != data->getOtherKV().end(); it ++)
                {
                        string akey = it->first;
                        string avalue = it->second;
                        pstmt->setString(1, data->getID());
                        pstmt->setString(2, akey);
                        pstmt->setString(3, avalue);
                        pstmt->excuteUpdate();
                }
                delete pstmt;

        }

        // Other
        if (data->getOtherKV().size() > 0)
        {
                pstmt = dbcon->prepareStatement(putother);
                map<string, string>:const_iterator it;
                for (it = data->getOtherKV.begin(); it != data->getOtherKV().end(); it ++)
                {
                        string akey = it->first;
                        string avalue = it->second;
                        pstmt->setString(1, data->getID());
                        pstmt->setString(2, akey);
                        pstmt->setString(3, avalue);
                        pstmt->excuteUpdate();
                }
                delete pstmt;

        }
}

