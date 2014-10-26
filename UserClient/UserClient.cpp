#include <iostream>
#include <QApplication>

#include "mainwindow.hpp"

QTcpSocket *establishConnection();

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    QTcpSocket *server = establishConnection();
    LoginManager *mainWindow = new LoginManager(server);
    
    mainWindow->mWindow = new MainWindow;
    mainWindow->mWindow->show();

    return app.exec();
}

QTcpSocket *establishConnection() {
    //just connect on localhost
    std::string servername = "127.0.0.1";
    std::string pnumstr = "23456";
    /*QRegExp portChk("^\\d{4,5}$");
    QRegExp ipChk("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
    std::cout << "Enter ip address (IP-IV) of server : ";
    std::string servername;
    std::cin >> servername;

    int matchpt = ipChk.indexIn(servername.c_str());
    if(matchpt < 0) {
        std::cout << "Invalid ip address!";
        exit(1);
    }
    std::cout << "Enter portnumber : ";
    std::string pnumstr;
    std::cin >> pnumstr;
    matchpt = portChk.indexIn(pnumstr.c_str());
    if(matchpt < 0) {
        std::cout << "Invalid port number!";
    }*/
    QTcpSocket *tcpSocket = new QTcpSocket(0);
    QString qhost = servername.c_str();
    QString qport = pnumstr.c_str();
    tcpSocket->connectToHost(qhost, qport.toInt());
    // Allow time for connection to establish, then check that all
    // looks good. If any problems, abort execution.
    bool ok = tcpSocket->waitForConnected(1000);
    if (!ok) {
        std::cout << "Wait for connected didn't work" << std::endl;
        exit(1);
    }
    if (!tcpSocket->isValid()) {
        std::cout << "Didn't connect completely?" << std::endl;
        exit(1);
    } QAbstractSocket::SocketState state;
    state = tcpSocket->state();
    if (state != QAbstractSocket::ConnectedState) {
        std::cout << "Not happy with state" << std::endl;
        exit(1);
    }
    
    return tcpSocket; 
} 
