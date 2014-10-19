#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

enum Request_t {ConferenceRequest, PaperRequest, UserRequest};

struct ClientHandler {
  ClientHandler(Request_t irequest) : Request_t(irequest)
    { }

Request_t request;

void handleClient();
bool authenticate(std::string, std::string);
bool connectToDB();

};
#endif
