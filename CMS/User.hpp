#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

enum UserType_t {NOUSER = 0, AUTHOR = 1, REVIEWER = 2, PCCHAIR = 3, ADMIN = 4};

struct User 
{
    User()
    {
        password = "";
        name = "no info";
        email = "no info";
        organisation = "no info";
        phone = "no info";
        userID = -1;
        userType = NOUSER;
//        currentPaper = Paper();
    }
    
    User(std::string& iuserName,
        std::string& iname,
        std::string& iemail,
        std::string& iorganisation,
        std::string& iphone,
        std::string& ipassword,
        int iuserID,
        std::vector<std::string>& ikeywords,
        UserType_t iUserType)
    {
        userName = iuserName;
        name = iname;
        email = iemail;
        organisation = iorganisation;
        phone = iphone;
        password = ipassword;
        userID = iuserID;
        keywords = ikeywords;
        userType = iUserType;
    }
    
    //no userID
    User(const std::string& iuserName,
        const std::string& iname,
        const std::string& iemail,
        const std::string& iorganisation,
        const std::string& iphone,
        const std::string& ipassword,
        const std::vector<std::string>& ikeywords,
        UserType_t iUserType)
    {
        userName = iuserName;
        name = iname;
        email = iemail;
        organisation = iorganisation;
        phone = iphone;
        password = ipassword;
        keywords = ikeywords;
        userType = iUserType;
    }

    std::string userName;
    std::string password;
    std::string name;
    std::string email;
    std::string organisation;
    std::string phone;
    std::vector<std::string> keywords;
    int userID;
    UserType_t userType;
};
#endif

