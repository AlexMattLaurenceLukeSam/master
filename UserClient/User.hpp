#ifndef USER_H
#define USER_H

#include "Paper.hpp"

#include <string>

enum UserType_t {Author, Reviewer, PCChair};

class User {
  public:
    User() { }
    User(const std::string& iuserName,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         const std::string& ipassword,
         int iuserID,
         UserType_t iuserType):
         userName(iuserName),
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         password(ipassword),
         userID(iuserID),
         userType(iuserType)
         { }
    virtual void view() = 0;
    void modifyDetails();
    void viewConferenceDetails();
    int getUserID() {return userID;}
    std::string getPassword() {return password;}
    std::string getName() {return name;}
    std::string getEmail() {return email;}
    std::string getOrganisation() {return organisation;}
    std::string getPhone() {return phone;}
    UserType_t getUserType() {return userType;}
    void setUserID(int iuserID) {userID = iuserID;}
    void setPassword(const std::string& ipassword) {password = ipassword;}
    void setName(const std::string& iname) {name = iname;}
    void setEmail(const std::string& iemail) {email = iemail;}
    void setOrganisation(const std::string& iorganisation) {organisation = iorganisation;}
    void setPhone(const std::string& iphone) {phone = iphone;}
    void setUserType(UserType_t iuserType) {userType = iuserType;}

    std::string userName;

  protected:

std::string password{""};
std::string name{""};
std::string email{""};
std::string organisation{""};
std::string phone{""};
int userID{0};
UserType_t userType;
Paper currentPaper;

};
#endif
