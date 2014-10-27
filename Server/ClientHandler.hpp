/*
 *    acts as the client for the server
 */

#ifndef CLIENTHANDLER_H
#define	CLIENTHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>

class ClientHandler : public QThread {
    Q_OBJECT

public:
    ClientHandler(int socketDescriptor, QObject *parent);

    void run();

private: 

    // handler functions here
    void handleLoginRequest();

    void handleOneRequest();
    bool getRequest();
    bool waitForBytes(int numbytes);

    void dispatchRequest();
    void prepareToRespond();
    void sendResponse(); 

    int socketDescriptor;
    QTcpSocket *tcpSocket;
    bool running;
    QByteArray requestData;
    QByteArray responseData; 

    QDataStream *requestReader;
    QDataStream *responseWriter; 

    UserManager* theUser = nullptr;
    
};

#endif	/* CLIENTHANDLER_H */


/* old stuff
#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

enum Request_t {ConferenceRequest, PaperRequest, UserRequest};

class ClientHandler {
public:
  ClientHandler(Request_t irequest) : request(irequest)
    { }
  Request_t getRequest() {return request;}   
  void setRequest(Request_t irequest) {request = irequest;}
  void handleClient();
  bool authenticate(std::string, std::string);
  bool connectToDB();
private:
  Request_t request;

};
#endif
*/
