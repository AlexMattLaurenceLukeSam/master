#ifndef PERSONAL_INFO_H 
#define PERSONAL_INFO_H

#include <vector>


struct PersonalInfo
{
    PersonalInfo()
    {
        infoID = 0;
        name = "";
        email = "";
        organisation = "";
        phone = "";
    }
    
    PersonalInfo(
        const std::string& iname,
        const std::string& iemail,
        const std::string& iorganisation,
        const std::string& iphone,
        int iinfoID)
    {
        name = iname;
        email = iemail;
        organisation = iorganisation;
        phone = iphone;
        infoID = iinfoID;
    }
    
    PersonalInfo(
        const std::string& iname,
        const std::string& iemail,
        const std::string& iorganisation,
        const std::string& iphone)
    {
        name = iname;
        email = iemail;
        organisation = iorganisation;
        phone = iphone;
    }

    int infoID;
    std::string name;
    std::string email;
    std::string organisation;
    std::string phone;
};

#endif
