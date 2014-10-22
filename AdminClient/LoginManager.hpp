#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "User.hpp"

struct LoginManager {
  LoginManager(bool iloggedIn) :
    loggedIn(iloggedIn)
    { }
  ~LoginManager() {
    delete currentUser;
  }
  bool loggedIn;
  bool login(std::string, std::string);
  void logout();
  User* currentUser{nullptr};
};
#endif
