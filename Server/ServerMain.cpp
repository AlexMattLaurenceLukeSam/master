/* 
 * File:   ServerMain.cpp
 * Author: ubuntu
 * 
 * Created on 23 October 2014, 2:40 AM
 */

#include <stdlib.h>
#include "ServerMain.hpp"
#include "ClientHandler.hpp"
#include <QtNetwork>
#include <iostream>

ServerMain::ServerMain(QObject *parent): 
{
    QTcpServer = parent;
    const char* arbitraryPort = "23456";
    this->portnum = arbitraryPort;

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost
                && ipAddressesList.at(i).toIPv4Address()) {
            this->ipAddress = ipAddressesList.at(i);
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (this->ipAddress.isNull())
        ipAddress = QHostAddress(QHostAddress::LocalHost);

    if (!this->listen(ipAddress,atoi(arbitraryPort))) {
        //using namespace std;
        std::cout << "Unable to initialize server listening port. Abort." << std::endl;
        exit(1);
    }
}

void ServerMain::incomingConnection(int socketDescriptor) 
{
    ClientHandler *handler = new ClientHandler(socketDescriptor, this);
    connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
    handler->start();
}

bool ServerMain::serverIsOK() 
{
    return this->isListening(); 
}
