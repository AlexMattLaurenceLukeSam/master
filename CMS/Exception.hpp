#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>
using namespace std;

class Exception : public exception {
public:
    Exception(string& whatsup) : message(whatsup) {  }
    ~Exception() throw() {}
    const char* what(){return message.c_str();}
private:
    string message;
};

#endif  

