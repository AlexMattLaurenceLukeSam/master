/* 
 * File:   UserClientStubForServer.cpp
 *      definition for UserClientStubForServer class
 *      acts as the server for the user client
 *      sends/handles requests/responses to/from the server
 * 
 * Authors: Alex Cremona, Sam Evans, Matthew Hollingsworth, Luke Mazur,
 *          Laurence Robinson-Mills
 */

#include "mainwindow.hpp"
#include "UserClientStubForServer.hpp"

void UserClientStubForServer::sendLoginRequest(QString uname, QString pword)
{
    if (this->busy)
        return;

    this->setupForRequest();
    this->setupForResponse(); // expecting a response to this request (omit otherwise)
    
    // Send a QString with command name as first on qdatastream
    QString checkLoginCmd = "CHECKLOGIN";
    
    (*this->requestWriter) << checkLoginCmd;
    (*this->requestWriter) << uname;
    (*this->requestWriter) << pword;
    this->sendRequest();
}

void UserClientStubForServer::handleLoginResponse()
{
    User* userResponse = new User;
    (*this->responseReader) >> userResponse;
    
    mainGui->setCurrentUser(userResponse);
    
    mainGui->loginResponse()
}

// receives response from server, takes qstring command off qdatastream, calls appropriate function
void UserClientStubForServer::dispatch(QString responseName) {
        
    // check command here and call appropriate handle function in LoginManager
    if (responseName == "CHECKLOGIN")
        handleLoginResponse();
}

void UserClientStubForServer::handleResponse() {
    QString responseName;
    (*this->responseReader) >> responseName;
    this->dispatch(responseName);
    this->busy = false; 
} 

void UserClientStubForServer::setupForRequest() {
    this->requestData.clear();
    this->requestWriter = new QDataStream(&requestData, QIODevice::WriteOnly);
    this->requestWriter->setVersion(QDataStream::Qt_4_0);
    // place a 4-byte "0" value in the data buffer - will overwrite with length
    // later
    (*this->requestWriter) << (quint32) 0;
    // Can now use requestWriter to write other elements of request to same
    // buffer
}

void UserClientStubForServer::sendRequest() {
    // Request is complete - just have to adjust the length field
    int datalength = this->requestData.size();
    
    datalength -= sizeof (quint32);
    this->requestWriter->device()->seek(0);
    (*this->requestWriter) << (quint32) datalength;
    
    // send it
    this->theServer->write(requestData);
    this->theServer->flush();
    
    // Now tidy up
    delete this->requestWriter; 
} 

void UserClientStubForServer::setupForResponse() {
    this->busy = true;
    // don't want any other requests made if need a response
    
    this->responseData.clear();
    this->responseLength = 0;
    this->responseLengthReceived = false;
    this->responseReader = new QDataStream(&responseData, QIODevice::ReadOnly);
    this->responseReader->setVersion(QDataStream::Qt_4_0);
}

void UserClientStubForServer::readResponseData() {
    // This function will be called repeatedly as the underlying system
    // detects incoming bytes on the tcp connection.
    
    // First four bytes represent length of data block with real response
    // Read these to set the hlocksize;
    // then, in effect, "wait" for the complete message to arrive
    // when message is complete, read the data into a buffer and call
    // a dispatch routine to handle response
    int headersize = sizeof (quint32);
    if (!this->responseLengthReceived) {
        // Waiting for the 4byte header
        if (theServer->bytesAvailable() < headersize) return; // not ready
        quint32 tmp;
        QDataStream in(theServer);
        in.setVersion(QDataStream::Qt_4_0);
        in >> tmp;
        
        this->responseLength = tmp;
        this->responseLengthReceived = true;
    } 

    // Waiting for the body of message
    if (theServer->bytesAvailable() < this->responseLength) return; // not ready

    this->responseData = theServer->read(this->responseLength);
    // message received, so process it
    this->handleResponse();
    // and tidy up
    delete this->responseReader;
}
