#ifndef USER_H
#define USER_H

#include <string>
#include <vector>


struct PersonalInfo {
  PersonalInfo() {}
  
  PersonalInfo(
         std::string& iname,
         std::string& iemail,
         std::string& iorganisation,
         std::string& iphone,
         std::string& ipassword,
         int iinfoID,
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         password(ipassword),
         infoID(iinfoID)
         { }

  PersonalInfo(
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         const std::string& ipassword,
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         password(ipassword),
         { }
  int infoID{0};
  std::string name{""};
  std::string email{""};
  std::string organisation{""};
  std::string phone{""};

};
#endif
