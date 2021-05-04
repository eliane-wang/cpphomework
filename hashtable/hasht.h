//hash header

#ifndef HASHT_H
#define HASHT_H

#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

class hasht {
 public:
  hasht();
  int Hash(char* key); //hash function
  void add(char* fname, char* lname, int id, float gpa); //adds student information to hash table
  void print(); //prints hash table
  void printIndex(int index); //prints students in each table index
  void del(char* fname); //deletes student from hash table
 private:
  static const int tableSize = 4;
  struct student {
    char* fname;
    char* lname;
    int id;
    float gpa;
    student* next;
  };
  student* hashTable[tableSize];
};

#endif