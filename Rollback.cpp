#include "Rollback.h" //everything just getting initalized

Rollback::Rollback() {

}

Rollback::~Rollback() {

}

Rollback::Rollback(string type, string action, int userID, bool needToDeleteMore) {
  this->type = type;
  this->action = action;
  this->userID = userID;
  this->needToDeleteMore = needToDeleteMore;
}

Rollback::Rollback(string type, string action, int newID, Faculty f) {
  this->type = type;
  this->action = action;
  this->newID = newID;
  this->f = f;
}

Rollback::Rollback(string type, string action, int stuID, Student s) {
  this->type = type;
  this->action = action;
  this->stuID = stuID;
  this->s = s;
}
