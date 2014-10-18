/*
 * File:        MyException.h
 * Author:      nabg
 *
 * Created on 27 November 2012, 11:20 AM
 */

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <string>
#include <exception>
using namespace std;

class MyException : public exception {
public:
    MyException(string& whatsup) : message(whatsup) {  }
    ~MyException() throw() {}
    const char* what(){return message.c_str();}
private:
    string message;
};

#endif  /* MYEXCEPTION_H */

