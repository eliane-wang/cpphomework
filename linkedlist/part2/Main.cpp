/* A program that uses a linked list to store information about students.
   Users can use the ADD, PRINT, DELETE, QUIT, and AVERAGE commands.

   Date: 04.15.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"
#include <iomanip>

using namespace std;
Node* add (Node* head, char* fname, char* lname, int newid, float newgpa);
void print(Node* next);
void quit(bool &running);
float averageGPA(Node* head);
float count(Node* head);
float sum(Node* head);
Node* del(Node* head, int id);
Node* head = NULL;

int main() {
  cout << "Student List Program" << endl;

  char command[7];
  bool running = true;
  while (running == true) { //program runs
    cout << "Commands: ADD PRINT DELETE QUIT AVERAGE" << endl;
    cin >> command;
    //ADD
    if (strcmp(command, "ADD") == 0) {
      cout << "First name? " << endl;
      char* fname = new char[20];
      cin >> fname;
      cout << "Last name? " << endl;
      char* lname = new char[20];
      cin >> lname;
      cout << "Student ID? " << endl;
      int newid;
      cin >> newid;
      cout << "Student GPA? " << endl;
      float newgpa;
      cin >> newgpa;
      head = add(head, fname,lname,newid,newgpa);
    }
    //PRINT
    else if (strcmp(command, "PRINT") == 0) {
      print(head);
    }
    //DELETE
    else if (strcmp(command, "DELETE") == 0) {
      cout << "Student ID to delete: " << endl;
      int id;
      cin >> id;
      head = del(head,id);
    }
    //QUIT
    else if (strcmp(command, "QUIT") == 0) {
      quit(running);
     }
    //AVERAGE
    else if (strcmp(command, "AVERAGE") == 0) {
      cout << "Average GPA: " << setprecision(2) << fixed << averageGPA(head) << endl;
    }
    //INVALID
    else {
      cout << "Invalid command! Try again." << endl;
    }
    cout << endl;
  }
}

//recursively add students to list in ascending order by ID
Node* add(Node* head, char* fname, char* lname, int newid, float newgpa){
  Node* temp = new Node(new Student(fname, lname, newid, newgpa));
  if (head == NULL|| !(head->getStudent()->getId() < newid)) { //insert before head 
    temp->setNext(head);
    return temp;
  }
  head->setNext(add(head->getNext(), fname, lname, newid, newgpa)); //recursion
  return head;
  
}

//recursively deletes student from linked list
Node* del(Node* temp, int id) {
  Node* next;
  if (temp == NULL) { //empty list
    cout << "Does not exist." << endl;
    return temp;
  }
  else if (temp->getStudent()->getId() == id) { //student to delete
    next = temp->getNext();
    temp->~Node();
    return next;
  }
  else { //recursion
    temp->setNext(del(temp->getNext(), id));
    return temp;
  }
}

//prints students from the linked list
void print(Node* next) {
  if (next == head) {
    cout << "Students: " << endl;
  }
  if (next != NULL) {
    cout << "Name: " << next->getStudent()->getFirstName() << " " << next->getStudent()->getLastName() << " ID: " << next->getStudent()->getId() << " GPA: " << setprecision(2) << fixed << next->getStudent()->getGpa() << endl;
    print (next->getNext());
  }
}

//quits 
void quit(bool &running) {
  running = false;
}

//finds the average student GPA
float averageGPA(Node* head) {
  return sum(head)/count(head);
}

//recursively sums all the GPAs
float sum(Node* head) {
 if (head == NULL) {
    return 0;
  }
  else {
    return head->getStudent()->getGpa() + sum(head->getNext());
  }
}

//counts number of nodes 
float count(Node* head) {
  Node* temp = head;
  int counter = 0;
  if (temp == NULL) {
    return 0;
  }
  while (temp != NULL) {
    counter++;
    temp = temp->getNext();
  }
  return counter;
}
