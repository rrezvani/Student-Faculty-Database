#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#include <iostream>
#include <string>

using namespace std;

class BaseClass {
  public:
    virtual void printMe() = 0;
    virtual void filePrint() = 0;
    int ID = 0;
    string name = "";
    string level = "";
    string college = "";
};

#endif
