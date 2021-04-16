/* Node Class 
 points to Student class */

#include <iostream>
#include "Node.h"

using namespace std;

//constructor
Node::Node(Student* newstudent) {
  studentptr = newstudent;
  next = NULL;
}

//destructor
Node::~Node() {
  delete &studentptr;
  next = NULL;
}

//get next Node pointer
Node* Node::getNext() {
  return next;
}

//set the next pointer to the corresponding node pointer
void Node::setNext(Node* newnext) {
  next = newnext;
}

//get student pointer
Student* Node::getStudent() {
  return studentptr;
}
