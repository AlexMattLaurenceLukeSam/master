/* 
 * File:   ServerMain.h
 * Author: ubuntu
 *
 * Created on 23 October 2014, 2:40 AM
 */

#ifndef SERVERMAIN_H
#define	SERVERMAIN_H

#include <QTcpServer>

class ServerMain : public QTcpServer {
    Q_OBJECT
    
public:
    ServerMain(QObject *parent = 0);
    QString listeningPort() { return this->portnum; }
    QString getIpAddress() { return this->ipAddress.toString(); }
    
    bool serverIsOK();
    
protected:
    void incomingConnection(int socketDescriptor);

private:
    QString portnum;
    QHostAddress ipAddress;

};


#endif	/* SERVERMAIN_H */

