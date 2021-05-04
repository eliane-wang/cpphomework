//hash

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "hasht.h"

using namespace std;

hasht::hasht() {
  //sets elements in hash table to empty or null
  for (int i = 0; i < tableSize; i++) {
    hashTable[i] = new student;
    hashTable[i]->fname = (char*)("empty");
    hashTable[i]->lname = (char*)("empty");
    hashTable[i]->id = 0;
    hashTable[i]->gpa = 0;
    hashTable[i]->next = NULL;
  }
}

int hasht::Hash(char* key) {
  int hash = 0;
  int index;
  for (int i = 0; i < strlen(key); i++) {
    hash = (hash + (int)key[i]);
  }
  index = hash%tableSize;
  return index;
}

//adds student information to hash table 
void hasht::add(char* fname, char* lname, int id, float gpa) {
  int index = Hash(fname);
  if (hashTable[index]->fname == (char*)("empty")) {
    //overwrite
    hashTable[index]->fname = fname;
    hashTable[index]->lname = lname;
    hashTable[index]->id = id;
    hashTable[index]->gpa = gpa;
  }
  else { //collision 
    student* ptr = hashTable[index];
    student* n = new student;
    n->fname = fname;
    n->lname = lname;
    n->id = id;
    n->gpa = gpa;
    n->next = NULL;
    while (ptr->next != NULL) { //traverse linked list
      ptr = ptr->next;
    }
    ptr->next = n;
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
  if (ptr->fname == (char*)("empty")) {
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
void hasht::del(char* fname) {
  int index = Hash(fname);
  student* delptr;
  student* p1;
  student* p2;
  //index empty
  if (hashTable[index]->fname == (char*)("empty") && hashTable[index]->lname == (char*)("empty")) {
    cout << fname << " was not found\n";
  }
  //index has one element
  else if (hashTable[index]->fname == fname && hashTable[index]->next == NULL) {
    hashTable[index]->fname = (char*)("empty");
    hashTable[index]->lname = (char*)("empty");
    hashTable[index]->id = 0;
    hashTable[index]->gpa = 0;
    cout << fname << " was removed\n";
  }
  //element is located in linked list
  else if (hashTable[index]->fname == fname) {
    delptr = hashTable[index];
    hashTable[index] = hashTable[index]->next;
    delete delptr;
    cout << fname << " was removed\n";
    
  }
  //
  else {
    p1 = hashTable[index]->next;
    p2 = hashTable[index];
    while (p1 != NULL && p1->fname != fname) {
      p2 = p1;
      p1 = p1->next;
    }
    if (p1 == NULL) { //no match
      cout << fname << " was not found\n";
    }
    else { //removing item
      delptr = p1;
      p1 = p1->next;
      p2->next = p1;
      delete delptr;
      cout << fname << " was removed\n";
    }
  }
}

