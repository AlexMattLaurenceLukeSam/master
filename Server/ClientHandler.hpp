#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H
#include <string>

Struct ClientHandler {
  ClientHandler(enum irequest) : request(irequest)
    { }

enum request;

void handleClient()
bool authenticate(std::string, std::string)
bool connectToDB()

};
#endif
