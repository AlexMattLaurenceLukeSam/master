#ifndef PERSONAL_INFO_H 
#define PERSONAL_INFO_H

#include <string>
#include <vector>


struct PersonalInfo {
  PersonalInfo() {}
  
  PersonalInfo(
         std::string& iname,
         std::string& iemail,
         std::string& iorganisation,
         std::string& iphone,
         int iinfoID
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone),
         infoID(iinfoID)
         { }

  PersonalInfo(
         const std::string& iname,
         const std::string& iemail,
         const std::string& iorganisation,
         const std::string& iphone,
         const std::string& ipassword
         ):
         name(iname),
         email(iemail),
         organisation(iorganisation),
         phone(iphone)
         { }
  int infoID{0};
  std::string name{""};
  std::string email{""};
  std::string organisation{""};
  std::string phone{""};

};
#endif
