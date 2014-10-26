//incomplete
#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "../DataAll/Conference.hpp"
#include "User.hpp"
#include "UserClientStubForServer.hpp"
//#include "mainwindow.hpp"

class MainWindow;

class LoginManager {
  public:
  LoginManager(QTcpSocket* aServer) {
      
    
    // Connection will mainly be managed by an instance of client stub class
    UserClientStubForServer *stub = new UserClientStubForServer(aServer, this);
    this->theServer = stub;
    // but do have some more initialisation to do on the connection
    aServer->setParent(this->theServer);
    // Read events generated through TCP connection to be handled by
    // instance of clientstub class
    QObject::connect(aServer, SIGNAL(readyRead()), stub, SLOT(readResponseData()));
    
//    mWindow = new MainWindow();
    
//    widget.setupUi(this);
    
//    connect(widget.loginButton, SIGNAL(clicked()), this,
//            SLOT(handleLoginButton()));
//    
//    connect(widget.quitButton, SIGNAL(clicked()), this, SLOT(close()));
    
    // Start things by sending a request for the names that are needed to
    // populate the list
    //this->theServer->getNames(); //ASYNCHRONOUS request - names will arrive sometime
    
  }
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
  MainWindow* mWindow;

// no other constructors deemed necessary at this point
  User* getCurrentUser() {return currentUser;}
  bool getLoggedIn() {return loggedIn;}
  void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}
  void setLoggedIn(bool iloggedIn) {loggedIn = iloggedIn;}  

  void loginRequest(QString, QString);
  void loginResponse();
  
  void logout();
  bool createAccount(std::string, std::string);
  void listConferences();
  void viewActiveConfDetails();
  Conference* getActiveConference() {return activeConference;}
  std::vector<Conference*> getConferences() {return conferences;}
  void setActiveConference(Conference* iactiveConference) {activeConference =  iactiveConference;}
  void setConferences(const std::vector<Conference*>& iconferences) {conferences =  iconferences;}
  std::vector<std::string> searchForKWords(std::string);
  void addToConferences(Conference* in) {
      conferences.push_back(in);
  }
  void removeConference(int conferenceToRemove) { //remove by paperID
    for(unsigned int i = 0; i < conferences.size(); ++i)
    {
      if(conferences[i]->confID == conferenceToRemove) {
        conferences.erase(conferences.begin() + i);
        return;
      }
    }
  } 

  private:
  User* currentUser{nullptr};
  bool loggedIn;
  std::vector<Conference*> conferences;
  Conference* activeConference{nullptr};
  UserClientStubForServer* theServer;

};
#endif
