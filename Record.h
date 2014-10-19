*
 * File:        MyRecord.cpp
 * Author:      nabg
 * 
 * Created on 23 November 2012, 1:25 PM
 * 
 * See MyRecord.h for some explanation!
 * 
 * class MyRecord {
public:
    explicit MyRecord(string& id); 
    void setName(string& aname) throw (MyException);
    void setEmail(string& amail) throw (MyException);
    void setInfo(string& info) throw (MyException);
    void setImage(string& imagestr) throw (MyException);
    void addRole(string& anotherrole) throw (MyException);
    void addKeyValue(string& collectionname, string& key, string& value) throw(MyException);

    string getID() const { return this->id; }
    string getName() const { return this->name; }
    string getEmail() const { return this->email; }
    string getInfo() const { return this->info; }
    string getImage() const { return this->image; }
    string getAttribute(string& collectionname, string& key) const throw(MyException);
    vector<string> getRoles() const { return this->roles; }
    map<string,string> getPhones() const { return this->phones; }
    map<string,string> getAddresses() const { return this->addresses; }
    map<string,string> getOtherKV() const { return this->other; }
    
    bool hasRole(string& queryrole) const;
    
private:
    string id; 
    string name; 
    string email; 
    string image;
    string info;
    vector<string> roles;
    map<string,string> phones;
    map<string,string> addresses;
    map<string,string> other;



 * 
 * 
 */

#include <vector>
#include <algorithm>
#include "MyRecord.h"
#include "stringtrimmer.h"

//#include <boost/regex.hpp>

MyRecord::MyRecord(string& id) {
    this->id = id;
}

void MyRecord::setName(string& aname) throw (MyException) {
    this->name = aname;
}

void MyRecord::setEmail(string& amail) throw (MyException) {
 //   boost::regex validationExpression("^[a-z0-9_\\+-]+(\\.[a-z0-9_\\+-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*\\.([a-z]{2,4})$");
 //   amail = trim(amail);
 //   boost::match_results<std::string::const_iterator> results;
 //   if (boost::regex_match(amail, results, validationExpression))
 //   {
        this->email = amail;
 //   }
 //   else
 //   {
 //       string msg = "Email of wrong format";
 //       throw MyException(msg);
 //   }
}

void MyRecord::setInfo(string& info) throw (MyException) {
    this->info = info;
}

void MyRecord::setImage(string& imagestr) throw (MyException) {
    this->image = imagestr;
}

void MyRecord::addRole(string& anotherrole)  {
    // Should it be an error to specify the same role more than once? No, it
    // will not really matter - so don't throw exception, just don't duplicate.
    vector<string>::iterator it;
    it = find(this->roles.begin(), this->roles.end(), anotherrole);
    if (it != this->roles.end()) return; // Found it, so don't duplicate
    roles.push_back(anotherrole);
}

void MyRecord::removeRole(std::string& oldrole)
{
    this->roles.erase(remove(this->roles.begin(),
        this->roles.end(), oldrole),
        this->roles.end());
}

void MyRecord::addKeyValue(string& collectionname, string& key, string& value) throw (MyException) {
    if (key.empty() || value.empty()) {
        string msg = "Empty key or value";
        throw MyException(msg);
    }
    // If same collection/key combination specified more than once, later value
    // overwrites earlier value for that key.

// Change to allow of rSTL's insert() not allowing for replacement
    if (collectionname == "Phones") {
        this->phones[key]=value;
    } else
        if (collectionname == "Addresses") {
        this->addresses[key]=value;
    } else
        if (collectionname == "Other") {
         this->other[key]=value;
    } else {
        string errmsg = "There is no collection called " + collectionname;
        throw MyException(errmsg);
    }
}

string MyRecord::getAttribute(string& collectionname, string& key) const throw (MyException) {


    if (collectionname == "Phones") {
        return phones.find(key)->second;
    } else
        if (collectionname == "Addresses") {
        return addresses.find(key)->second;
    } else
        if (collectionname == "Other") {
        return other.find(key)->second;
    }

    string errmsg = "There is no collection called " + collectionname;
    throw MyException(errmsg);

}


bool MyRecord::hasRole(string&  anotherrole) const  {
    // Should it be an error to specify the same role more than once? No, it
    // will not really matter - so don't throw exception, just don't duplicate.
    vector<string>::const_iterator it;
    it = find(this->roles.begin(), this->roles.end(), anotherrole);
   return(it != this->roles.end()) ;
}
