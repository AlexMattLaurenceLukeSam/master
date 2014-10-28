#include <iostream>
#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) 
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    MainWindow mWindow;
    mWindow.show();

    return app.exec();
}
