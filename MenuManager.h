#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <iostream>
#include <string>
#include "linkedlist.h"
#include "BaseClass.h"
#include "Student.h"
#include "Faculty.h"
#include "BST.h"
#include "linkedlist.h"
#include "Rollback.h"
#include "GenStack.h"
#include <fstream>

class MenuManager {
  public:
    MenuManager();
    ~MenuManager();
    void printAllStudents();
    void printAllFaculty();
    void printSpecificStudent(int userID);
    void printSpecificFaculty(int userID); //all the functions
    void printFacultyGivenStudent(int stuID);
    void printAdviseesGivenFaculty(int facID);
    void deleteStudent(int stuID);
    void deleteFaculty(int facID);
    void undoDeleteFaculty(int facID);
    void undoDeleteStudent(int stuID);
    void changeAdvisor(int stuID);
    void removeAdvisee(int facID);
    void undoAction();
    void addStudent();
    void addFaculty();
    void outputFile();
    void facultyPreorderTraversal(TreeNode<Faculty> *node);
    void studentPreorderTraversal(TreeNode<Student> *node);
    void readFile();

  private:
    BST<Student> *masterStudent;
    BST<Faculty> *masterFaculty; //BSTs

    GenStack<Rollback> *rStack; //rollback

    int studentID;
    int advisorIDConst;
    string studentName;
    string studentGrade; //all our variables
    string studentMajor;
    string placeHolder;
    double studentGPA;

    int facultyID;
    string facultyName;
    string level;
    string department;
    int adviseeID;
    int tempNum;
    int newID;

    ifstream studentInput;
    ifstream facultyInput;
    ofstream studentFile;
    ofstream facultyFile;
    string fileSentence;

    int position;
    int stuID;
    int facID;
    int advID;
    int numAdvisors;
    string leveL;
    string dept;
    string name;
    string grade;
    string major;
    double gPA;
    int advisorID;

    DoublyLinkedList<int> *dl;
};

#endif
