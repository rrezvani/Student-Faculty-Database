#include "Student.h"

Student::Student() {
  ID = 0;
  name = "DefaultName";
  level = "DefaultLevel";
  college = "DefaultCollege";
  GPA = 0;
  advisorID = 0;
}

Student::~Student() {

}

Student::Student(int stuID) {
  ID = stuID;
}

Student::Student(int stuID, string stuName, string grade, string major, double gradePointAverage, int facultyID) {
  ID = stuID;
  name = stuName;
  level = grade;
  college = major;
  GPA = gradePointAverage;
  advisorID = facultyID;
}

void Student::setAdvisorID(int facID) {
  advisorID = facID;
  cout << advisorID << "from function" << endl;
}

void Student::printMe() {
  cout << "ID: " << ID << endl << "Name: " << name << endl << "Grade: " << level << endl << "Major: " << college << endl << "GPA: " << GPA << endl << "Advisor ID: " << advisorID << endl << endl;
}

void Student::filePrint() {
  ofstream stu;

  stu.open("studentTable.txt", ios::app); //append to file

  stu << ID << endl << name << endl << level << endl << college << endl << GPA << endl << advisorID << endl << endl;

  stu.close();
}

bool Student::operator==(const Student& stu1) {
  return (this->ID == stu1.ID);
}

bool Student::operator<(const Student& stu1) {
  return (this->ID < stu1.ID);
}

bool Student::operator>(const Student& stu1) {
  return (this->ID < stu1.ID);
}

bool Student::operator!=(const Student& stu1) {
  return (this->ID != stu1.ID);
}
