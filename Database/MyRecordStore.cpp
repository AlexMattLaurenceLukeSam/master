#include "MyRecordStore.h"

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

using namespace sql;

const char* databaseStr = "localhost";
const char* databaseUserName = "matt";
const char* databaseUserPassword = "nuria1990";
const char* databaseSchema = "csci222";

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
        const char* countrecord = "select count(*) from myrecord where _id=?";
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

std::vector<std::string> *MyRecordStore::allKeys()
{
        if (invalid)
                throw (noDB);
        std::vector<std::string> *vptr = new std::vector<std::string>();

        const char* selectall = "select _id from MyRecord";
        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(selectall);

        rs = pstmt->executeQuery();
        while (rs->next()) {
                std::string anid = rs->getString(1);
                vptr->push_back(anid);
        }

        return vptr;
}
std::vector<MyRecord*> *MyRecordStore::getInRole(const char* role) throw (const char*)
{
        if (invalid)
                throw (noDB);
        // Laboured
        // First get a list of the ids with the role, then one by one get the
        // complete records.
        const char* getrolepersons = "selects personid from roles where _role=?";

        sql::PreparedStatement *pstmt = NULL;
        sql::ResultSet * rs = NULL;

        pstmt = dbcon->prepareStatement(getrolepersons);
        pstmt->setString(1, role);
        rs = pstmt->executeQuery();

        bool haveRecord = rs->next();
        if (!haveRecord)
        {
                delete rs;
                delete pstmt;
                return NULL;
        }

        std::vector<std::string> people;

        // rc = sqlite3_step(stmt);

        while (rs->next()) {
                std::string apersonid = std::string(rs->getString(1));
//              const char* apersonid = reinterpret_cast<const char*> (rs->getString(2));
                people.push_back(apersonid);
        }

        // Maybe there weren't any
        if (people.size() == 0)
                return NULL;

        // Build collection by getting each record
        std::vector<MyRecord*> *roleholders = new std::vector<MyRecord*>();

        std::vector<std::string>::const_iterator it;
        for (it = people.begin(); it != people.end(); it++) {
                std::string aperson = *it;
                MyRecord* rec = this->get(aperson.c_str());
                roleholders->push_back(rec);
        }

        return roleholders;
}
//
//      sqlite3_stmt* stmt;
//      int rc;
//      rc = sqlite3_prepare_v2(db,
//              getrolepersons, strlen(getrolepersons),
//              &stmt, &unused);
//      if (rc != SQLITE_OK) {
//              std::cerr << prepareFailed << std::endl;
//              exit(1);
//      }
//
//      rc = sqlite3_bind_text(stmt, 1, role, -1 , SQLITE_STATIC);
//      if (rc != SQLITE_OK) {
//              std::cerr << bindFailed << std::endl;
//              exit(1);
//      }
//      std::vector<std::string> people;
//
//      // rc = sqlite3_step(stmt);
//
//      while (sqlite3_step(stmt) == SQLITE_ROW) {
//              const char* apersonid = reinterpret_cast<const char*> (sqlite3_column_text(stmt, 0));
//              people.push_back(apersonid);
//      }
//      sqlite3_finalize(stmt);
//
//
//      // Maybe there weren't any
//      if (people.size() == 0)
//              return NULL;
//
//      // Build collection by getting each record
//      std::vector<MyRecord*> *roleholders = new std::vector<MyRecord*>();
//
//      std::vector<std::string>::const_iterator it;
//      for (it = people.begin(); it != people.end(); it++) {
//              std::string aperson = *it;
//              MyRecord* rec = this->get(aperson.c_str());
//              roleholders->push_back(rec);
//      }
//      
//      return roleholders;
//}     

void MyRecordStore::put(const char* key, const MyRecord *data) throw (const char*)
{

        if (invalid)
                throw (noDB);

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
        const char* deletephones = "delete from phones where personid=?";
        const char* deleteaddress = "delete from addresses where personid=?";
        const char* deleteother = "delete from other where personid=?";
        const char* deleteroles = "delete from roles where personid=?";
        const char* deletemyrecord = "delete from myrecord where _id=?";
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
        delete pstmt;

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
        const char* getrecord = "select * from myrecord where _id=?";
        const char* getroles = "select role from roles where personid=?";
        const char* getphones = "select type, number from phones where personid=?";
        const char* getaddress = "select type, address from addresses where personid=?";
        const char* getother = "select key, valyue from other where personid=?";

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

        std::string id = rs->getString(1);
        std::string name = rs->getString(2);
        std::string email = rs->getString(3);
        std::string info = rs->getString(4);
        std::string image = rs->getString(5);

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
                std::string arole = rs->getString(1);
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

        const char* putmyrecord = "insert into myrecord values( ?, ?, ?, ?, ?)";
        const char* putrole = "insert into roles values(?, ?)";
        const char* putphone = "insert into phones values (?, ?, ?)";
        const char* putaddress = "insert into addresses values (?, ?, ?)";
        const char* putother = "insert into other values (?, ?, ?)";

        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(putmyrecord);
        pstmt->setString(1, data->getID());
        pstmt->setString(2, data->getName());
        pstmt->setString(3, data->getEmail());
        pstmt->setString(4, data->getInfo());
        pstmt->setString(5, data->getImage());

        pstmt->executeUpdate();

        delete pstmt;

        // Role 
//      if (data->getOtherKV().size() > 0)
//      {
//              pstmt = dbcon->prepareStatement(putother);
//              std::map<std::string, std::string>::const_iterator it;
//              for (it = data->getRoles().begin(); it != data->getRoles().end(); it ++)
//              {
//                      std::string akey = it->first;
//                      std::string avalue = it->second;
//                      pstmt->setString(1, data->getID());
//                      pstmt->setString(2, akey);
//                      pstmt->setString(3, avalue);
//                      pstmt->executeUpdate();
//              }
//              delete pstmt;
//
//      }

//      // Other
//      if (data->getOtherKV().size() > 0)
//      {
//              pstmt = dbcon->prepareStatement(putother);
//              std::map<std::string, std::string>::const_iterator it;
//              for (it = data->getOtherKV.begin(); it != data->getOtherKV().end(); it ++)
//              {
//                      std::string akey = it->first;
//                      std::string avalue = it->second;
//                      pstmt->setString(1, data->getID());
//                      pstmt->setString(2, akey);
//                      pstmt->setString(3, avalue);
//                      pstmt->executeUpdate();
//              }
//              delete pstmt;
//
//      }
}
