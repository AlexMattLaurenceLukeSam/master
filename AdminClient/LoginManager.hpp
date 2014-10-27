#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include "User.hpp"
#include "AdminClientStubForServer.hpp"

class MainWindow;

class LoginManager 
{
public:
    LoginManager(QTcpSocket* aServer) 
    {
      // Connection will mainly be managed by an instance of client stub class
      AdminClientStubForServer *stub = new AdminClientStubForServer(aServer, this);
      this->theServer = stub;
      // but do have some more initialisation to do on the connection
      aServer->setParent(this->theServer);
      // Read events generated through TCP connection to be handled by
      // instance of clientstub class
      QObject::connect(aServer, SIGNAL(readyRead()), stub, SLOT(readResponseData()));
    
    }

    LoginManager(bool iloggedIn)
    {
        loggedIn = iloggedIn;
    }

    ~LoginManager() 
    {
        delete currentUser;
    }
    
    MainWindow* mWindow;
    
    bool getLoggedIn() {return loggedIn;}
    User* getCurrentUser() {return currentUser;}
    void setLoggedIn(bool iloggedIn) {loggedIn = iloggedIn;}
    void setCurrentUser(User* icurrentUser) {currentUser = icurrentUser;}  
    
    bool login(std::string, std::string);
    void logout();
  
private:
    bool loggedIn;
    User* currentUser = nullptr;
    AdminClientStubForServer* theServer;
};
#endif
