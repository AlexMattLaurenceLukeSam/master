#include <iostream>
#include <QApplication> // NOTE: might need to be <QtGui/QApplication>

#include "Author.hpp"
#include "Conference.hpp"
#include "Date.hpp"
#include "Discussion.hpp"
#include "DiscussionPost.hpp"
#include "LoginManager.hpp"
#include "Paper.hpp"
#include "PCChair.hpp"
#include "Review.hpp"
#include "Reviewer.hpp"
#include "User.hpp"

#include "mainwindow.hpp" //NOTE: used for testing atm

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow *foo = new MainWindow();
    
    foo->show();
    
    // create and show your widgets here

    return app.exec();
}
