/* HashT Class */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "hasht.h"

using namespace std;

//constructor
hasht::hasht() {
  //sets elements in hash table to empty or null
  tableSize = 100;
  hashTable = new student*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    hashTable[i] = NULL;
  }
}

//hash function
int hasht::Hash(int id) {
  int hash = id%tableSize;
  return hash;
}

//adds student information to hash table 
void hasht::add(char* fname, char* lname, int id, float gpa) {
  int index = Hash(id);
  student* current = hashTable[index];
  if (current == NULL) {
    //overwrite
    hashTable[index] = new student();
    current = hashTable[index];
    current->fname = fname;
    current->lname = lname;
    current->id = id;
    current->gpa = gpa;
  }
  else { //collision
    student* ptr = hashTable[index];
    student* n = new student;
    //add student
    n->fname = fname;
    n->lname = lname;
    n->id = id;
    n->gpa = gpa;
    n->next = NULL;
    //chain to end of linked list 
    int collisionCount = 1;
    while (ptr->next != NULL) {
      ptr = ptr->next;
      collisionCount++;
    }
    ptr->next = n;
    //more than 3 collisions
    if (collisionCount >= 3) {
      resize();
    }    
  }
}

//double the size of the hash table if there are more than 3 collisions
void hasht::resize() {
  //create a table with double the spots
  tableSize = 2*tableSize; 
  student** oldTable = hashTable;
  hashTable = new student*[tableSize]; //reassign
  for (int i = 0; i < tableSize; i++) {
    hashTable[i] = NULL;
  }
  for (int h = 0; h < tableSize/2; h++) { //each student
    student* ptr = oldTable[h];
    if (ptr != NULL) { //not empty 
      while (ptr != NULL) { //traverse linked list
	add(ptr->fname, ptr->lname, ptr->id, ptr->gpa); 
	ptr = ptr->next;
      }
    }
  }
  delete oldTable;
}

//prints hash table and first student in linked list
void hasht::print() {
  for (int i = 0; i < tableSize; i++) { //each index
    printIndex(i);
   }
}

//prints students in each table index
void hasht::printIndex(int index) {
  student* ptr = hashTable[index];
  if (ptr == NULL) { //no students
      cout << "INDEX " << index << " IS EMPTY" << endl;
  }
  else { //prints students
    cout << "---------------------\n";
    cout << "INDEX " << index << " -------------\n";
    while (ptr != NULL) {
      cout << "\t" << ptr->fname << " ";
      cout << ptr->lname << endl;
      cout << "\tID: " << ptr->id << endl;
      cout << "\tGPA:" << ptr->gpa << endl;
      cout << "\t-------------\n";
      ptr = ptr->next;
    }
  }
}

//deletes student from hash table
void hasht::del(int id) {
  int index = Hash(id);
  student* delptr;
  student* p1;
  student* p2;
  //index empty
  if (hashTable[index] == NULL) {
    cout << "Student with ID " << id << " was not found\n";
  }
  //index has one element
  else if (hashTable[index]->id == id && hashTable[index]->next == NULL) {
    hashTable[index] = NULL;
    cout << "Student with ID " << id << " was removed\n";
  }
  //student is first in linked list
  else if (hashTable[index]->id == id) {
    delptr = hashTable[index];
    hashTable[index] = hashTable[index]->next;
    delete delptr;
    cout << "Student with ID " << id << " was removed\n";
    
  }
  //student is located in linked list
  else {
    p1 = hashTable[index]->next;
    p2 = hashTable[index];
    while (p1 != NULL && p1->id != id) {
      p2 = p1;
      p1 = p1->next;
    }
    if (p1 == NULL) { //no match
      cout << "Student with ID " << id << " was not found\n";
    }
    else { //removing student
      delptr = p1;
      p1 = p1->next;
      p2->next = p1;
      delete delptr;
      cout << "Student with ID " << id << " was removed\n";
    }
  }
}

