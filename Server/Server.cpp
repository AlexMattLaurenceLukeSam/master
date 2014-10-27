//NEW MAIN FOR SERVER

#include "ConferenceManager.hpp"
#include "PaperManager.hpp"
#include "UserManager.hpp"

#include <iostream>
#include <QApplication>
#include "ServerMain.hpp"

int main(int argc, char *argv[])
{
//  Database* db;
//  PaperManager* pm;
//  ConferenceManager* cm;
//  UserManager* um;
//    
//  db = new Database(/*CONSTRUCTOR*/);
//  pm = new PaperManager(nullptr, db);
//  cm = new ConferenceManager(std::vector<Conference*>(), db, nullptr);
//  um = new UserManager(nullptr, db);
  

    std::cout << "Server application starting" << std::endl;
    std::cout << "Initializing QT framework" << std::endl;
    QApplication app(argc, argv);
    std::cout << "Creating threaded network server" << std::endl;
    ServerMain *theServer = new ServerMain();
    std::cout << "Server location: " << theServer->getIpAddress().toStdString()
              << ":" << theServer->listeningPort().toStdString() << std::endl;
    if(!theServer->serverIsOK()) {
        std::cout << "Failed" << std::endl;
        std::exit(1);
    }
  
    
    // create and show your widgets here
//    gDialogptr = new Dialog();
//    return gDialogptr->exec();
  
    // GO! GO! GO!
    int rtnValue = app.exec();
   
//  delete um;
//  delete cm;
//  delete pm;
//  delete db;

    return rtnValue;
}
