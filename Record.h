/*
 * File:        MyRecord.h
 * Author:      nabg
 *
 * Created on 27 November 2012, 11:18 AM
 */

#ifndef MYRECORD_H
#define MYRECORD_H
#include "MyException.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class MyRecord {
public:
    explicit MyRecord(std::string& id); // I don't want implicit conversion from std::std::string to MyRecord!
    // Mutator functions - setting of other fields
    // In this version, hardly any of the implementations will actually throw exceptions
    // later validation functions will be added
    void setName(std::string& aname) throw (MyException);
    void setEmail(std::string& amail) throw (MyException);
    void setInfo(std::string& info) throw (MyException);
    void setImage(std::string& imagestr) throw (MyException);
    void addRole(std::string& anotherrole) ;
    void removeRole(std::string& oldrole);
    void addKeyValue(std::string& collectionname, std::string& key, std::string& value) throw(MyException);
    // Accessor functions

    std::string getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getEmail() const { return this->email; }
    std::string getInfo() const { return this->info; }
    std::string getImage() const { return this->image; }
    std::string getAttribute(std::string& collectionname, std::string& key) const throw(MyException);
    const std::vector<std::string>& getRoles() const { return this->roles; }
    const std::map<std::string,std::string>& getPhones() const { return this->phones; }
    const std::map<std::string,std::string>& getAddresses() const { return this->addresses; }
    const std::map<std::string,std::string>& getOtherKV() const { return this->other; }

    bool hasRole(std::string& queryrole) const;

private:
    std::string id; // Also known as "nickname", or even "primary key"
    std::string name; // full name
    std::string email;
    std::string image;
    std::string info;
    std::vector<std::string> roles;
    std::map<std::string,std::string> phones;
    std::map<std::string,std::string> addresses;
    std::map<std::string,std::string> other;
     // Finally, note that copy constructor and assignment operator are
    // private (and no implementations will be defined).  I choose to 
    // disallow such operations.
    MyRecord(const MyRecord& orig);
    MyRecord& operator=(const MyRecord&);
    // Further there is no virtual destructor, I do not intend MyRecord
    // to be the base class in some hierarchy.
};

#endif  /* MYRECORD_H */
