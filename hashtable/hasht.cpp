//hash

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "hasht.h"

using namespace std;

hasht::hasht() {
  //sets elements in hash table to empty or null
  tableSize = 4;
  hashTable = new student*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    hashTable[i] = NULL;
  }
}

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
    current->fname = fname;
    current->lname = lname;
    current->id = id;
    current->gpa = gpa;
  }
  else { //collision
    int collisionCount = 1;
    while (current->next != NULL) {
      current = current->next;
      collisionCount++;
    }
    //add
    current->fname = fname;
    current->lname = lname;
    current->id = id;
    current->gpa = gpa;
  }
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
  if (ptr == NULL) {
      cout << "INDEX " << index << " IS EMPTY" << endl;
  }
  else {
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
    hashTable[index]->fname = (char*)("empty");
    hashTable[index]->lname = (char*)("empty");
    hashTable[index]->id = 0;
    hashTable[index]->gpa = 0;
    cout << "Student with ID " << id << " was removed\n";
  }
  //element is located in linked list
  else if (hashTable[index]->id == id) {
    delptr = hashTable[index];
    hashTable[index] = hashTable[index]->next;
    delete delptr;
    cout << "Student with ID " << id << " was removed\n";
    
  }
  //
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
    else { //removing item
      delptr = p1;
      p1 = p1->next;
      p2->next = p1;
      delete delptr;
      cout << "Student with ID " << id << " was removed\n";
    }
  }
}

