#include "Simulation.h"

Simulation::Simulation() {
  menuManager = new MenuManager();
}

Simulation::~Simulation() {
  delete menuManager;
}

void Simulation::simulate() {
  cout << "Press 1 to read in from file, press any other number to start from scratch: ";
  getline(cin, placeHolder); //if you mix getline() with cin it can create issues, so I used getline for the entire assignment and used stoi and stod as needed
  userNum = stoi(placeHolder);

  if (userNum == 1) {
    menuManager->readFile(); //if the user wants to read in from file, we will
  }

  displayMenu(); //show the menu
  getline(cin, placeHolder);
  userNum = stoi(placeHolder);

  while (userNum != 14) { //run until they want to exit
    int digitHolder = 0;
    switch (userNum) { //won't explain much here, this is just calling every respective funciton depending on what the user picks
      case 1:
        menuManager->printAllStudents();
        break;
      case 2:
        menuManager->printAllFaculty();
        break;
      case 3:
        cout << "Student ID you would like to print: "; //most functions require an ID, so if needed we ask them here and use it as a parameter to our other function
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->printSpecificStudent(digitHolder);
        break;
      case 4:
        cout << "Faculty ID you would like to print: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->printSpecificFaculty(digitHolder);
        break;
      case 5:
        cout << "Please enter the student ID in order to print their respective faculty member's information: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->printFacultyGivenStudent(digitHolder);
        break;
      case 6:
        cout << "Please enter the faculty ID in order to print their respective advisee information: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->printAdviseesGivenFaculty(digitHolder);
        break;
      case 7:
        menuManager->addStudent();
        break;
      case 8:
        cout << "Please enter the student ID in order to delete them: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->deleteStudent(digitHolder);
        break;
      case 9:
        menuManager->addFaculty();
        break;
      case 10:
        cout << "Please enter the faculty ID in order to delete them: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->deleteFaculty(digitHolder);
        break;
      case 11:
        cout << "Please enter the student ID so we can change their advisor: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->changeAdvisor(digitHolder);
        break;
      case 12:
        cout << "Please enter the faculty ID to remove an advisee: ";
        getline(cin, placeHolder);
        digitHolder = stoi(placeHolder);
        menuManager->removeAdvisee(digitHolder);
        break;
      case 13:
        menuManager->undoAction();
        break;
    }
    displayMenu();
    getline(cin, placeHolder);
    userNum = stoi(placeHolder);
  }


  cout << "Thanks for joining!" << endl;
  menuManager->outputFile(); //outputs everything to the file at the end
}

void Simulation::displayMenu() { //menu
  cout << "1. Print all students and their information" << endl;
  cout << "2. Print all faculty and their information" << endl;
  cout << "3. Display student information" << endl;
  cout << "4. Display faculty information" << endl;
  cout << "5. Print a student's faculty advisor" << endl;
  cout << "6. Print a faculty member's advisees" << endl;
  cout << "7. Add a new student" << endl;
  cout << "8. Delete a student" << endl;
  cout << "9. Add a new faculty member" << endl;
  cout << "10. Delete a faculty member" << endl;
  cout << "11. Change a student's advisor" << endl;
  cout << "12. Remove an advisee from a faculty member" << endl;
  cout << "13. Undo" << endl;
  cout << "14. Exit" << endl << endl;
  cout << "Please select what choice you would like: ";
}
