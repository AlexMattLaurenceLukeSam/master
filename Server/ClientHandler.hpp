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
