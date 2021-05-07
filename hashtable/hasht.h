/* HashT Class Header */

#ifndef HASHT_H
#define HASHT_H

#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

class hasht {
 public:
  hasht(); //constructor
  int Hash(int id); //hash function
  void add(char* fname, char* lname, int id, float gpa); //adds student information to hash table
  void resize(); //double the size of the table if there are more than 3 collisions 
  void print(); //prints hash table
  void printIndex(int index); //prints students in each table index
  void del(int id); //deletes student from hash table
 private:
  int tableSize;
  struct student {
    char* fname;
    char* lname;
    int id;
    float gpa;
    student* next;
  };
  student** hashTable;
};

#endif
