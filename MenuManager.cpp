#include "MenuManager.h"

MenuManager::MenuManager() {
  masterStudent = new BST<Student>();
  masterFaculty = new BST<Faculty>();
  rStack = new GenStack<Rollback>();
}

MenuManager::~MenuManager() {
  delete masterStudent;
  delete masterFaculty;
  delete rStack;
}

void MenuManager::readFile() {
  studentInput.open("studentTable.txt"); //opening file

  if (studentInput.is_open()) {
    while (!studentInput.fail()) {
      getline(studentInput, fileSentence); //read in line
      switch (position) {
        case 0:
          stuID = stoi(fileSentence); //first line is ID
          position++;
          break;
        case 1:
          name = fileSentence; //second is name
          position++;
          break;
        case 2:
          grade = fileSentence; //third is grade
          position++;
          break;
        case 3:
          major = fileSentence; //fourth is major
          position++;
          break;
        case 4:
          gPA = stod(fileSentence); //fifth is gpa
          position++;
          break;
        case 5:
          advisorID = stoi(fileSentence); //sixth is advisor
          position++;
          break;
        case 6:
        {
          position = 0; //on the seventh, we set it back to 0, and make our student/insert it in the BST
          Student s(stuID, name, grade, major, gPA, advisorID);
          masterStudent->insert(s);
          break;
        }
        default:
          break;
      }
    }
  }
  studentInput.close(); //close file

  facultyInput.open("facultyTable.txt"); //open file
  position = 0; //make sure position is at 0
  if (facultyInput.is_open()) {
    while (!facultyInput.fail()) {
      getline(facultyInput, fileSentence);
      switch (position) {
        case 0:
          facID = stoi(fileSentence); //first line is ID
          position++;
          break;
        case 1:
          name = fileSentence; //second is name
          position++;
          break;
        case 2:
          leveL = fileSentence; //third is level
          position++;
          break;
        case 3:
          dept = fileSentence; //fourth is department
          position++;
          break;
        case 4:
        {
          numAdvisors = stoi(fileSentence); //fifth is num advisors
          DoublyLinkedList<int> *dll = new DoublyLinkedList<int>();
          for (int i = 0; i < numAdvisors; ++i) { //iterates numAdvisor amount of times
            getline(facultyInput, fileSentence);
            advID = stoi(fileSentence);
            dll->InsertBack(advID); //inserts into dll
          }
          Faculty f(facID, name, leveL, dept, dll); //creates and inserts faculty into bst
          masterFaculty->insert(f);
          position++;
          break;
        }
        case 5:
          position = 0;
          break;
        default:
          break;
      }
    }
  }
  facultyInput.close();
}

void MenuManager::facultyPreorderTraversal(TreeNode<Faculty> *node) { //preorder traversal of the faculty BST
  ofstream fac;

  fac.open("facultyTable.txt", ios::app); //opens with append

  if (fac.is_open()) {
    node->key.filePrint(); //print to file
    if (node->left != NULL) {
      facultyPreorderTraversal(node->left); //recursive method
    }
    if (node->right != NULL) {
      facultyPreorderTraversal(node->right);
    }
  }
  fac.close();
}

void MenuManager::studentPreorderTraversal(TreeNode<Student> *node) { //preorder traversal of the student BST
  ofstream stu;
  stu.open("studentTable.txt", ios::app); //opens with append

  if (stu.is_open()) {
    node->key.filePrint();
    if (node->left != NULL) {
      studentPreorderTraversal(node->left);
    }
    if (node->right != NULL) {
      studentPreorderTraversal(node->right);
    }
  }
  stu.close();
}

void MenuManager::outputFile() {
  facultyFile.open("facultyTable.txt", ios::trunc); //overwrites whatever was left from before

  if (facultyFile.is_open()) {
    TreeNode<Faculty> *f = masterFaculty->getRoot(); //get the root and start the preorder traversal with it
    facultyPreorderTraversal(f);
  }
  facultyFile.close();

  studentFile.open("studentTable.txt", ios::trunc);
  if (studentFile.is_open()) {
    TreeNode<Student> *s = masterStudent->getRoot(); //same as above
    studentPreorderTraversal(s);
  }
  studentFile.close();

}

void MenuManager::printAllStudents() {
  TreeNode<Student> *krump = masterStudent->getRoot(); //start the root, then use it to do an inorder traversal
  masterStudent->recPrintStudent(krump); //call the inorder traversal
}

void MenuManager::printAllFaculty() {
  TreeNode<Faculty> *krump = masterFaculty->getRoot(); //same concept as above
  masterFaculty->recPrintFaculty(krump);
}

void MenuManager::printSpecificStudent(int userID) {
  Student s = masterStudent->getNode(userID); //gets the student object
  if (masterStudent->contains(s)) {
    s.printMe(); //prints its information
  }
  else {
    cout << "ID not in the database" << endl;
  }
}

void MenuManager::printSpecificFaculty(int userID) {
  Faculty f = masterFaculty->getNode(userID); //gets the faculty object
  if (masterFaculty->contains(f)) {
    f.printMe(); //prints its information
  }
  else {
    cout << "ID not in the database" << endl;
  }
}

void MenuManager::printFacultyGivenStudent(int stuID) {
  Student s = masterStudent->getNode(stuID);
  if (masterStudent->contains(s)) {
    Faculty f = masterFaculty->getNode(s.advisorID); //find the faculty using the students advisor ID
    f.printMe(); //print the faculty object
  }
  else {
    cout << "ID not in the database" << endl;
  }
}

void MenuManager::printAdviseesGivenFaculty(int facID) {
  Faculty f = masterFaculty->getNode(facID);
  if (masterFaculty->contains(f)) {
    ListNode<int> *current = f.adviseesID->ReturnListNode(); //gets the first of the dll
    while (current != NULL) {
      Student s = masterStudent->getNode(current->data); //current->data is simply the ID, so we are getting the student object given the ID
      s.printMe(); //printing the students info
      current = current->next; //moving to next node
    }
    cout << endl;
  }
  else {
    cout << "ID not in the database" << endl;
  }
}

void MenuManager::addStudent() {
  cout << "Student ID: ";
  getline(cin, placeHolder);
  studentID = stoi(placeHolder);

  if (!masterStudent->contains(studentID)) {//making sure the student doesn't already exist
    cout << "Name: ";
    getline(cin, studentName);

    cout << "Grade: ";
    getline(cin, studentGrade);

    cout << "Major: ";
    getline(cin, studentMajor);

    cout << "GPA: ";
    getline(cin, placeHolder);
    studentGPA = stod(placeHolder);

    cout << "Advisor ID: ";
    getline(cin, placeHolder);
    advisorIDConst = stoi(placeHolder);

    if (!masterFaculty->contains(advisorIDConst)) { //if the advisor does not exist, we will make one
      cout << "We need to add this faculty because he/she/they doesn't exist! Please answer the following questions, thanks!" << endl;

      facultyID = advisorIDConst;

      cout << "Name: ";
      getline(cin, facultyName);

      cout << "Level: ";
      getline(cin, level);

      cout << "Department: ";
      getline(cin, department);

      DoublyLinkedList<int> *dl = new DoublyLinkedList<int>();

      adviseeID = studentID;

      dl->InsertBack(adviseeID);


      Faculty f1(facultyID, facultyName, level, department, dl); //make the new faculty
      masterFaculty->insert(f1); //insert the new faculty

      Rollback r("faculty", "insert", facultyID, false);
      rStack->push(r);

      Rollback r1("student", "insert", studentID, true); //document the double insert that happened
      rStack->push(r1);
    }

    else {
      cout << "This faculty already exists!" << endl;
      Faculty f = masterFaculty->getNode(advisorIDConst); //if the faculty already exists, we find the faculty object and add the new student to the adviseesList
      f.adviseesID->InsertBack(studentID);

      Rollback r2("student", "insert", studentID, false); //document the single insert
      rStack->push(r2);
    }

    Student s(studentID, studentName, studentGrade, studentMajor, studentGPA, advisorIDConst); //make the student
    masterStudent->insert(s); //put it in the tree
  }
  else {
    cout << "This student already exists!" << endl;
  }
}

void MenuManager::addFaculty() { //exact same logic as addStudent()
  cout << "Faculty ID: ";
  getline(cin, placeHolder);
  facultyID = stoi(placeHolder);

  if (!masterFaculty->contains(facultyID)) {
    cout << "Name: ";
    getline(cin, facultyName);

    cout << "Level: ";
    getline(cin, level);

    cout << "Department: ";
    getline(cin, department);

    cout << "Advisee ID: ";
    getline(cin, placeHolder);
    adviseeID = stoi(placeHolder);
    DoublyLinkedList<int> *dl1 = new DoublyLinkedList<int>();

    if (!masterStudent->contains(adviseeID)) {
      cout << "We need to add this student because he/she/they don't exist! Please answer the following questions, thanks!" << endl;
      studentID = adviseeID;

      cout << "Name: ";
      getline(cin, studentName);

      cout << "Grade: ";
      getline(cin, studentGrade);

      cout << "Major: ";
      getline(cin, studentMajor);

      cout << "GPA: ";
      getline(cin, placeHolder);
      studentGPA = stod(placeHolder);

      advisorIDConst = facultyID;

      dl1->InsertBack(adviseeID);

      Student s1(studentID, studentName, studentGrade, studentMajor, studentGPA, advisorIDConst); //make the student
      masterStudent->insert(s1); //insert it

      Rollback r("student", "insert", studentID, false); //document the double insert
      rStack->push(r);

      Rollback r1("faculty", "insert", facultyID, true);
      rStack->push(r1);
    }
    else {
      cout << "Student exists!" << endl;

      Rollback r2("faculty", "insert", facultyID, false); //document the single insert
      rStack->push(r2);
    }
    Faculty f(facultyID, facultyName, level, department, dl1); //make the faculty
    masterFaculty->insert(f); //insert it
  }
  else {
    cout << "Faculty ID already exists!" << endl;
  }
}

void MenuManager::deleteStudent(int stuID) {
  Student s = masterStudent->getNode(stuID);
  if (masterStudent->contains(s)) {
    Faculty f = masterFaculty->getNode(s.advisorID); //remove the student from the faculty members adviseesList
    f.adviseesID->Remove(stuID);
    Rollback r("student", "delete", stuID, s); //document the delete
    rStack->push(r);
    masterStudent->deleteNode(s); //delete the node
  }
}

void MenuManager::deleteFaculty(int facID) {
  Faculty f = masterFaculty->getNode(facID);
  if (masterFaculty->contains(f)) {

    ListNode<int> *current = f.adviseesID->ReturnListNode(); //go through the adviseesList and relocate all the students that will be left with no advisor
    while (current != NULL) {

      cout << "Before we can delete this advisor, we need to relocate the student associated with it, please enter a new advisor ID: ";
      getline(cin, placeHolder);
      newID = stoi(placeHolder);
      if (masterFaculty->contains(newID)) {
        TreeNode<Student> *node = masterStudent->getTreeNode(current->data); //getting the treenode so we can alter the data
        node->key.advisorID = newID; //changes the student advisor ID to whatever the newID is

        Faculty newFac = masterFaculty->getNode(newID);
        newFac.adviseesID->InsertBack(current->data); //adding the student to the new faculty members adviseesList
      }
      else {
        cout << "This new ID doesn't have a faculty member, try again" << endl;
      }
      current = current->next; //moving to the next node
    }
    Rollback r3("faculty", "delete", newID, f); //documenting the delete
    rStack->push(r3);
    masterFaculty->deleteNode(f); //deleting the node
  }
}

void MenuManager::changeAdvisor(int stuID) {
  Student s = masterStudent->getNode(stuID);
  if (masterStudent->contains(s)) {
    Faculty f = masterFaculty->getNode(s.advisorID);
    f.adviseesID->Remove(stuID); //remove student from old faculty member adviseesList

    cout << "Please input the new faculty ID: ";
    getline(cin, placeHolder);
    newID = stoi(placeHolder);

    Faculty newFac = masterFaculty->getNode(newID);

    if (masterFaculty->contains(newFac)) {
      TreeNode<Student> *node = masterStudent->getTreeNode(stuID); //student treenode
      node->key.advisorID = newID; //changing the advisor ID to the newID

      newFac.adviseesID->InsertBack(stuID); //putting the student in the new adviseesList
    }
    else {
      cout << "Faculty does not exist" << endl;
    }

  }
}

void MenuManager::removeAdvisee(int facID) {
  Faculty f = masterFaculty->getNode(facID);
  if (masterFaculty->contains(f)) {
    cout << "Here are the available students to remove" << endl;
    ListNode<int> *current = f.adviseesID->ReturnListNode();
    while (current != NULL) { //quickly print all available students to remove for simplicity
      Student s = masterStudent->getNode(current->data);
      cout << "ID: " << s.ID << endl; //printing each respective student's id
      current = current->next;
    }
    cout << "Which student would you like to remove: ";
    getline(cin, placeHolder);
    tempNum = stoi(placeHolder);

    f.adviseesID->Remove(tempNum); //remove whatever the user chose

    cout << "Your student now needs a new faculty member, please enter a faculty ID to reassign them: ";
    getline(cin, placeHolder);
    newID = stoi(placeHolder);

    Faculty newFac = masterFaculty->getNode(newID);

    if (masterFaculty->contains(newFac)) {
      TreeNode<Student> *node = masterStudent->getTreeNode(tempNum);
      node->key.advisorID = newID; //assign the new advisor ID to the student

      newFac.adviseesID->InsertBack(tempNum);
    }

  }

}

void MenuManager::undoDeleteFaculty(int facID) { //these are methods only used in rollback, a delete with no documentation
  Faculty f = masterFaculty->getNode(facID);
  if (masterFaculty->contains(f)) {
    masterFaculty->deleteNode(f);
  }
}

void MenuManager::undoDeleteStudent(int stuID) { //these are methods only used in rollback, a delete with no documentation
  Student s = masterStudent->getNode(stuID);
  if (masterStudent->contains(s)) {
    masterStudent->deleteNode(s);
  }
}

void MenuManager::undoAction() {
  Rollback r4 = rStack->pop(); //get the most recent action

  if (r4.action == "insert") { //if insert, enter this loop
    if (r4.type == "student") { //if student
      if (r4.needToDeleteMore) { //if student that was double inserted with a faculty in the same move
        undoDeleteStudent(r4.userID); //delete student
        Rollback r5 = rStack->pop(); //pop next one
        undoDeleteFaculty(r5.userID); //delete faculty
      }
      else { //if only a single insert
        Faculty f = masterFaculty->getNode(masterStudent->getNode(r4.userID).advisorID); //f equal to the student's advisor ID
        f.adviseesID->Remove(r4.userID); //removing the student from the faculty adviseesList
        undoDeleteStudent(r4.userID); //deleting the student
      }
    }
    else if (r4.type == "faculty") { //if faculty that was inserted
      if (r4.needToDeleteMore) {
        undoDeleteFaculty(r4.userID); //double insert == double delete
        Rollback r6 = rStack->pop();
        undoDeleteStudent(r6.userID);
      }
      else {
        undoDeleteFaculty(r4.userID); //single insert == single delete
      }
    }
  }
  else if (r4.action == "delete") { //if delete, enter this loop
    if (r4.type == "faculty") { //if faculty was deleted
      ListNode<int> *current = r4.f.adviseesID->ReturnListNode(); //get the front of the dll
      while (current != NULL) {
        TreeNode<Student> *node = masterStudent->getTreeNode(current->data); //student treenode using our adviseeList
        node->key.advisorID = r4.f.ID; //changing the student's advisor ID to what it was before

        Faculty f = masterFaculty->getNode(r4.newID);
        f.adviseesID->Remove(node->key.ID); //removing the student from the old faculty member
        current = current->next;
      }
      masterFaculty->insert(r4.f); //inserting the faculty member back in
    }
    else if (r4.type == "student") { //if student delete
      Faculty f = masterFaculty->getNode(r4.s.advisorID);
      f.adviseesID->InsertBack(r4.s.ID); //insert the student back into its faculty members adviseesList
      masterStudent->insert(r4.s); //insert the student
    }
  }
}
