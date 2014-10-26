#ifndef USER_H
#define USER_H

#include "../DataAll/Paper.hpp"

#include <string>

enum UserType_t {AUTHOR, REVIEWER, PCCHAIR};

class User {
  public:
    User() { }
    User(const std::string& iuserName,
         const std::string& ipassword,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         int iuserID,
         UserType_t iuserType):
         userName(iuserName),
         password(ipassword),
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         userID(iuserID),
         userType(iuserType)
         { }
    virtual ~User() {}
    
//    virtual void view() = 0;
    virtual void modifyDetails();
    void viewConferenceDetails();
    int getUserID() {return userID;}
    std::string getPassword() {return password;}
    std::string getName() {return name;}
    std::string getEmail() {return email;}
    std::string getOrganisation() {return organisation;}
    std::string getPhone() {return phone;}
    UserType_t getUserType() {return userType;}
    Paper getCurrentPaper() {return currentPaper;}
    void setUserID(int iuserID) {userID = iuserID;}
    void setPassword(const std::string& ipassword) {password = ipassword;}
    void setName(const std::string& iname) {name = iname;}
    void setEmail(const std::string& iemail) {email = iemail;}
    void setOrganisation(const std::string& iorganisation) {organisation = iorganisation;}
    void setPhone(const std::string& iphone) {phone = iphone;}
    void setUserType(UserType_t iuserType) {userType = iuserType;}
    void setCurrentPaper(const Paper& icurrentPaper) {currentPaper = icurrentPaper;}

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
