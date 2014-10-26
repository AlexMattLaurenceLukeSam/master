/* 
 * File:   UserClientStubForServer.hpp
 *      header for UserClientStubForServer class
 *      acts as the server for the user client
 *      sends/handles requests/responses to/from the server
 * 
 * Authors: Alex Cremona, Sam Evans, Matthew Hollingsworth, Luke Mazur,
 *          Laurence Robinson-Mills
 */

#ifndef USERCLIENTSTUBFORSERVER_H
#define	USERCLIENTSTUBFORSERVER_H

#include <QtCore>
#include <QtNetwork>

class LoginManager;

class UserClientStubForServer : public QObject {
    
    Q_OBJECT;
public:
    UserClientStubForServer(QTcpSocket *aServer, LoginManager* aMainGui) {
        this->theServer = aServer;
        this->mainGui = aMainGui;
        this->busy = false;
    }
    
    // The communications are asynchronous - so the requests are "void"
    // a request is sent; if a response is expect, the link is marked as busy
    // any other requests will be discarded
    
    // Sometime a response will arrive - because its a network connection
    // the response may come as several separate blocks of bytes 
    // When a complete response is received, it is handled - there is a
    // dispatcher function that recognises the different reponses and
    // calls appropriate "call-back" functions that adjust data in the form
    
    // NOTE: functions for requests sent to server go here
    // sendFooRequest()
    void sendLoginRequest(QString uname, QString pword);
   
public slots:
    void readResponseData(); 

private:
    void setupForRequest();
    void sendRequest();
    void setupForResponse();
    void handleResponse();
    // Specific response handler routines
    void dispatch(QString responseName);
    
    // NOTE: functions to handle responses from server go here
    // handleFooResponse())
    void handleLoginResponse();
    
    // NOTE: probably delete
    // Don't define copy constructor
    // UserClientStubForServer(const UserClientStubForServer&) {}
private:
    bool busy;
    QByteArray requestData;
    QDataStream *requestWriter;
    
    QByteArray responseData;
    QDataStream *responseReader;
    bool responseLengthReceived;
    int responseLength; 

    // Collaborators 
    QTcpSocket *theServer;
    LoginManager *mainGui; // used to send server responses to/from gui

};

#endif	/* USERCLIENTSTUBFORSERVER_H */
