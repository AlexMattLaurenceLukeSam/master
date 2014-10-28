//NEW MAIN FOR SERVER

#include "ConferenceManager.hpp"
#include "PaperManager.hpp"
#include "UserManager.hpp"

#include <iostream>
#include <QApplication>
#include "ServerMain.hpp"

int main(int argc, char *argv[])
{
    Database* db;
    PaperManager* pm;
    ConferenceManager* cm;
    UserManager* um;

    db = new Database(/*CONSTRUCTOR*/);
    pm = new PaperManager(NULL, db);
    cm = new ConferenceManager(std::vector<Conference*>(), db, NULL);
    um = new UserManager(NULL, db);

    delete um;
    delete cm;
    delete pm;
    delete db;

    return 0;
}
