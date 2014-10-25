#include "LoginManager.hpp"

//NOTE: temporarily commented out parameters to silence compiler warning until implemented
bool LoginManager::login(std::string /*username*/, std::string /*password*/)
{
//    UserType_t uType;//from packet

//        if(username == "PCChair" && password == "admin")
//            uType = AUTHOR;
//        else if(username == "Reviewer" && password == "user")
//            uType = REVIEWER;
//        else if(username == "Author" && password == "user")
//            uType = PCCHAIR;


//    std::vector<std::string> keys;
//    std::vector<PaperSummary> papers;
//    std::string blank = "";
//    if(uType == AUTHOR){
//        currentUser = new Author(username, blank, blank, blank, blank, 0, AUTHOR);
//        currentUser->setUserType(AUTHOR);
//        return true;
//    } else if (uType == REVIEWER){
//        currentUser = new Reviewer(username, "", "", "", "", 0, REVIEWER);
//        currentUser->setUserType(REVIEWER);
//        return true;
//    } else if (uType == PCCHAIR) {
//        currentUser = new PCChair(username, "", "", "", "", 0, PCCHAIR);
//        currentUser->setUserType(PCCHAIR);
//        return true;
//    } else return false;

    //this function sends the username and password to the server for verification
    //the response received is used to construct the currentUser pointer member of loginmanager


    return false; // NOTE: placeholder
}

void LoginManager::logout()
{
    //no server client interaction
    //acts as a destructor basically
}

//NOTE: temporarily commented out parameters to silence compiler warning until implemented
bool LoginManager::createAccount(std::string /*username*/, std::string /*password*/)
{
    //this functions identically to login except that a new record is created in the database with the supplkied details
    //rather than verifying that one exists with matching details
    
    return false; // NOTE: placeholder
}
