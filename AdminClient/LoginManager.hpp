#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H
Struct LoginManager {
  LoginManager(bool iloggedIn) :
    loggedIn(iloggedIn)
    { }
  bool loggedIn;
  bool login(std::string, std::string)
  void logout()
};
#endif
