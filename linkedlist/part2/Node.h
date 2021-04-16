/* Node Class Header */
#include <iostream>
#include "Student.h"

using namespace std;

class Node {
 public:
  Node(Student*); //constructor
  ~Node(); //destructor
  Node* getNext(); //get next node pointer
  void setNext(Node* newnext); //set the next pointer to corresponding node pointer
  Student* getStudent(); //get student pointer
private:
  Node* next; //next node
  Student* studentptr; //student pointer
};
