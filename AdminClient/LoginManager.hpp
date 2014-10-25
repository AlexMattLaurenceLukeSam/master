#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "User.hpp"

class LoginManager {
public:
  LoginManager(bool iloggedIn) :
    loggedIn(iloggedIn)
    { }
  ~LoginManager() {
    delete currentUser;
  }
  bool getLoggedIn() {return loggedIn;}
  User* getCurrentUser() {return currentUser;}
  void setLoggedIn(bool iloggedIn) {loggedIn = iloggedIn;}
  void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}  
  
  bool login(std::string, std::string);
  void logout();
  
private:
  bool loggedIn;
  User* currentUser{nullptr};
};
#endif
