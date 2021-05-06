#ifndef ROLLBACK_H
#define ROLLBACK_H

#include <iostream>
#include <string>

#include "Faculty.h"
#include "Student.h"

using namespace std;

class Rollback {
  public:
    Rollback();
    ~Rollback();
    Rollback(string type, string action, int userID, bool needToDeleteMore); //rollback object for an insert
    Rollback(string type, string action, int newID, Faculty f); //rollback object for a faculty delete
    Rollback(string type, string action, int stuID, Student s); //rollback object for a student delete

    string type;
    string action;
    int userID;
    int newID;
    int stuID;
    bool needToDeleteMore;
    Faculty f;
    Student s;
};

#endif
