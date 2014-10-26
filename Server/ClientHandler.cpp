/* 
 * 
 */

#include "ClientHandler.hpp"
#include "UserManager.hpp"
//#include "UserList.h" NOTE: old
#include <iostream> 

#include <QtNetwork>

ClientHandler::ClientHandler(int socketDescriptor, QObject* parent)
    : QThread(parent), socketDescriptor(socketDescriptor) {
    this->tcpSocket = NULL;
}

void ClientHandler::run() { // DO NOT TOUCH
    //using namespace std;
    std::cout << "Handling a new client at socketDescriptor " << this->socketDescriptor << std::endl;
    this->tcpSocket = new QTcpSocket(0);
    this->tcpSocket->setSocketDescriptor(this->socketDescriptor);
    
    this->running = true;
    while (this->running)
        handleOneRequest();
    
    std::cout << "Client terminated on socketOescriptor " << this->socketDescriptor << std::endl;
    if (this->tcpSocket->state() == QAbstractSocket::ConnectedState) {
        this->tcpSocket->disconnectFromHost();
        this->tcpSocket->waitForDisconnected();
    }
}

void ClientHandler::handleOneRequest() { // DO NOT TOUCH
    if (this->getRequest())
        this->dispatchRequest(); 
}

bool ClientHandler::getRequest() { //DO NOT TOUCH
    //using namespace std;
    requestData.clear();
    // Requests:
    // there is a 4byte integer in Ot's wire format that specifies
    // size of the data portion
    // then there is a data portion of some number of bytes 

    // Wait, with timeout, for the 4byte header
    // Then wait again for all the data to arrive before reading data.

    if (!this->waitForBytes((int) sizeof (quint32)))
        return false;

    quint32 blockSize;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    in >> blockSize;
    if (!waitForBytes((int) blockSize)) return NULL;

    // Simply read the bytes into requestData - leave it to the dispatch
    // function to sort out what information is there. 

    this->requestData = this->tcpSocket->read(blockSize);
    return true; 
} 

bool ClientHandler::waitForBytes(int numbytes) { // DO NOT TOUCH
    //using namespace std; 

    const int Timeout = 500000;
    while (tcpSocket->bytesAvailable() < numbytes) {
        bool ready = tcpSocket->waitForReadyRead(Timeout);

        if (!ready) {
            // "wait for ready read" will return false if no bytes received
            // and have timed out
            // abortOnError("time out while waiting data on socket");
            this->running = false;
            return false;
        }
        // more bytes received, but were they sufficient in number?
    }
    // Finally have required number of bytes
    return true; 
}

// receives request from client, takes qstring command off qdatastream, calls appropriate function
void ClientHandler::dispatchRequest() {

    requestReader = new QDataStream(&requestData, QIODevice::ReadOnly);
    requestReader->setVersion(QDataStream::Qt_4_0);
    QString cmd;
    (*requestReader) >> cmd;
    
    // check command here and call appropriate function
    if (cmd == "CHECKLOGIN")
        this->handleLoginRequest();

    delete requestReader;
    this->requestData.clear();
}

void ClientHandler::handleLoginRequest() {
    // extract objects after command qstring
    QString uname;
    QString pword;
    (*requestReader) >> uname;
    (*requestReader) >> pword;

    prepareToRespond(); // only if response needed
    
    // interact with whatever to interact with database here
    // check if user exists and check password
    theUser->fetchUser(uname.toStdString());
    if (theUser->getCurrentUser()->password != pword.toStdString()) {
        theUser->setCurrentUser(nullptr);
    }
    
    // if needed send response
    // first qstring is a command
    QString cmd = "CHECKLOGIN";
    (*this->responseWriter) << cmd;
    
    // write the rest of the response
    (*this->responseWriter) << theUser->getCurrentUser();
    
    // sendResponse
    this->sendResponse(); 
}

void ClientHandler::prepareToRespond() { // DO NO TOUCH
    this->responseData.clear(); 
    this->responseWriter = new QDataStream(&responseData, QIODevice::WriteOnly);
    this->responseWriter->setVersion(QDataStream::Qt_4_0);
    // place a 4-byte "0" value in the data buffer - will overwrite with length
    // later
    (*this->responseWriter) << (quint32) 0;
    // Can now use responseWriter to write other elements of request to same
    // buffer; 
}

void ClientHandler::sendResponse() { // DO NOT TOUCH
    // Request is complete - just have to adjust the length field
    int datalength = this->responseData.size();

    datalength -= sizeof (quint32);

    this->responseWriter->device()->seek(0);
    (*this->responseWriter) << (quint32) datalength; 

    // send it
    tcpSocket->write(responseData);
    tcpSocket->flush();

    // Now tidy up
    delete this->responseWriter; 
} 
