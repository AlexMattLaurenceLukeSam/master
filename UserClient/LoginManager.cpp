#include "LoginManager.hpp"

void LoginManager::loginRequest(std::string username, std::string password)
{

//    theServer->sendLoginRequest(username, password);
    
    //this function sends the username and password to the server for verification
    //the response received is used to construct the currentUser pointer member of loginmanager

}

void LoginManager::loginResponse()
{
//    if (currentUser == NULL) {
//        loggedIn = false;
//        std::string msg = "Incorrect username/password!";
//        mWindow->errorBox(msg);
//        mWindow->noUser();
//    }
}

void LoginManager::logout()
{
    //no server client interaction
    //acts as a destructor basically
}

//NOTE: temporarily commented out parameters to silence compiler warning until implemented
bool LoginManager::createAccount(std::string username, std::string password)
{
    //this functions identically to login except that a new record is created in the database with the supplkied details
    //rather than verifying that one exists with matching details
    
    return false; // NOTE: placeholder
}
