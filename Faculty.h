#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include "BaseClass.h"
#include "linkedlist.h"
#include <fstream>

using namespace std;

class Faculty : public BaseClass {
  public:
    Faculty();
    ~Faculty();
    Faculty(int facID);
    Faculty(int facID, string facName, string profession, string department, DoublyLinkedList<int> *tempIDS);
    void printMe(); //functions that print / write to file
    void filePrint();

    bool operator==(const Faculty& fac1); //overload operators
    bool operator<(const Faculty& fac1);
    bool operator>(const Faculty& fac1);
    bool operator!=(const Faculty& fac1);

    DoublyLinkedList<int> *adviseesID;
};

#endif
