/* First part of student list program that uses linked lists.

   Date: 04.11.2021
   Author: Eliane Wang */
   

#include <iostream>
#include "Student.h"
#include "Node.h"

using namespace std;
void add(char* fname, char* lname, int newid, float newgpa);
void print(Node* next);
Node* head = NULL; //first node

int main() {
  //adds student info
  add((char*)("ellen"), (char*)("degeneres"), 1, 2.8);
  add((char*)("kim"), (char*)("kardashian"), 2, 3.4);
  add((char*)("danny"), (char*)("devito"), 3, 4.5);
  add((char*)("jacob"), (char*)("sartorius"), 4, 3.1);
  add((char*)("jojo"), (char*)("siwa"), 5, 3.3);
  print(head); //prints all students
  
}

//add students to the linked list
void add(char* fname, char* lname, int newid, float newgpa){
  Node* temp = head;
  if (temp == NULL) {
    head = new Node(new Student (fname, lname, newid, newgpa));
  }
  else {
    while (temp->getNext() != NULL) {
      temp = temp->getNext();
    }
    temp->setNext(new Node(new Student (fname, lname, newid, newgpa)));
  }
}

//prints students from the linked list
void print(Node* next) {
  if (next == head) {
    cout << "Students: " << endl;
  }
  if (next != NULL) {
    cout << "Name: " << next->getStudent()->getFirstName() << " " << next->getStudent()->getLastName() << " ID: " << next->getStudent()->getId() << " GPA: " << next->getStudent()->getGpa() << endl;
    print (next->getNext());
  }
}
    

