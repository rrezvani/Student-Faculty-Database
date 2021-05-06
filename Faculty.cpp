#include "Faculty.h"

Faculty::Faculty() {
  ID = 0;
  name = "DefaultName";
  level = "DefaultLevel";
  college = "DefaultCollege";
}

Faculty::~Faculty() {

}

Faculty::Faculty(int facID) {
  ID = facID;
}

Faculty::Faculty(int facID, string facName, string profession, string department, DoublyLinkedList<int> *tempIDS) {
  ID = facID;
  name = facName;
  level = profession;
  college = department;
  adviseesID = tempIDS;
}

bool Faculty::operator==(const Faculty& fac1) {
  return (this->ID == fac1.ID);
}

bool Faculty::operator<(const Faculty& fac1) {
  return (this->ID < fac1.ID);
}

bool Faculty::operator>(const Faculty& fac1) {
  return (this->ID > fac1.ID);
}

bool Faculty::operator!=(const Faculty& fac1) {
  return (this->ID != fac1.ID);
}

void Faculty::printMe() {
  cout << "ID: " << ID << endl << "Name: " << name << endl << "Level: " <<  level << endl << "Department: " << college << endl;

  ListNode<int> *currNode = adviseesID->ReturnListNode(); //get the front of the dll
  while (currNode != NULL) {
    cout << "Advisee ID: " << currNode->data << endl; //prints advisee ID out repetitively until it's NULL
    currNode = currNode->next;
  }
  cout << endl;
}

void Faculty::filePrint() {
  ofstream fac;

  fac.open("facultyTable.txt", ios::app);

  fac << ID << endl << name << endl << level << endl << college << endl << adviseesID->GetSize() << endl;
  ListNode<int> *currNode = adviseesID->ReturnListNode();
  while (currNode != NULL) {
    fac << currNode->data << endl;
    currNode = currNode->next;
  }
  fac << endl;
  fac.close();
}
