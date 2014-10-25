/* 
 * File:   AdminClientStubForServer.hpp
 *      header for AdminClientStubForServer class
 *      acts as the server for the admin client
 *      sends/handles requests/responses to/from the server
 * 
 * Authors: Alex Cremona, Sam Evans, Matthew Hollingsworth, Luke Mazur,
 *          Laurence Robinson-Mills
 */

#ifndef USERCLIENTSTUBFORSERVER_H
#define	USERCLIENTSTUBFORSERVER_H

#include <qt4/Qt/QtCore>
#include <qt4/Qt/QtNetwork>

class MainWindow;

class AdminClientStubForServer : public QObject {
    
    Q_OBJECT;
public:
    AdminClientStubForServer(QTcpSocket *aServer, MainWindow* aMainGui) {
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
    void checkLoginDetails(QString uname, QString pword); // NOTE: example
   
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
    void handleCheckLoginDetailsResponse(); // NOTE: example
    
    // NOTE: probably delete
    // Don't define copy constructor
    // AdminClientStubForServer(const AdminClientStubForServer&) {}
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
    MainWindow *mainGui; // used to send server responses to gui NOTE: was LoginManager *theLoginForm;

};

#endif	/* USERCLIENTSTUBFORSERVER_H */
