#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
#include "BaseClass.h"

using namespace std;

class Student : public BaseClass {
  public:
    Student();
    ~Student();
    Student(int stuID);
    Student(int stuID, string stuName, string grade, string major, double gradePointAverage, int facultyID);
    void printMe(); //functions that print / write to file
    void filePrint();

    void setAdvisorID(int facID);

    bool operator==(const Student& stu1); //overload operators
    bool operator<(const Student& stu1);
    bool operator>(const Student& stu1);
    bool operator!=(const Student& stu1);

    double GPA;
    int advisorID;
};


#endif
