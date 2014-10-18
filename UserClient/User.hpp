#ifndef USER_H
#define USER_H

#include <string>

Class User {
  public:
    User(const std::string& iusername,
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         const std::string& ipassword,
         int iuserID):
         username(iusername),
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         password(ipassword),
         userID(iuserID)
         { }
    virtual void view() = 0;
    void modifyDetails()
    void viewConferenceDetails()
    std::string getUserID() {return userID;}
    std::string getPassword() {return password;}
    std::string getName() {return name;}
    std::string getEmail() {return email;}
    std::string getOrganisation() {return organisation;}
    std::string getPhone() {return phone;}
    void setUserID(int iuserID) {userID = iuserID;}
    void setPassword(const std::string& ipassword) {password = ipassword;}
    void setName(const std::string& iname) {name = iname;}
    void setEmail(const std::string& iemail) {email = iemail;}
    void setOrganisation(const std::string& iorganisation) {organisation = iorganisation;}
    void setPhone(const std::string& iphone) {phone = iphone;}

    std::string username;

  protected:

std::string password;
std::string name;
std::string email;
std::string organisation;
std::string phone;
int userID{0};

};
#endif
