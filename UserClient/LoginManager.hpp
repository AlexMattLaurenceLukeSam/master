//incomplete
#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "Conference.hpp"
#include "User.hpp"

class LoginManager {
  public:
  LoginManager() { }
  LoginManager(bool iloggedIn,
               const std::vector<Conference*>& iconferences,
               Conference* iactiveConference) :
               loggedIn(iloggedIn),
               conferences(iconferences),
               activeConference(iactiveConference) // potentially useful for logging back into the conference they were last in
               { }
  ~LoginManager() {
  for (unsigned i=0; i < conferences.size(); i++) {
    delete conferences[i];
  }
  delete currentUser;
}

// no other constructors deemed necessary at this point
  User* getCurrentUser() {return currentUser;}
  bool getLoggedIn() {return loggedIn;}
  void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}
  void setLoggedIn(bool iloggedIn) {loggedIn = iloggedIn;}  

  bool login(std::string, std::string);
  void logout();
  bool createAccount(std::string, std::string);
  void listConferences();
  void viewActiveConfDetails();
  Conference* getActiveConference() {return activeConference;}
  std::vector<Conference*> getConferences() {return conferences;}
  void setActiveConference(Conference* iactiveConference) {activeConference =  iactiveConference;}
  void setConferences(const std::vector<Conference*>& iconferences) {conferences =  iconferences;}
  std::vector<std::string> searchForKWords(std::string);


  private:
  User* currentUser{nullptr};
  bool loggedIn;
  std::vector<Conference*> conferences;
  Conference* activeConference{nullptr};

};
#endif
