/* Student Header */

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {
 public:
  Student(char* fname, char* lname,int newid,float newgpa); //constructor
  char* getFirstName(); //get student first name
  char* getLastName(); //get student last name
  int getId(); //get id
  float getGpa(); //get gpa
private:
  Student* studentptr; //student pointer
  char* firstname; //student first name
  char* lastname; //student last name
  int id; //student id
  float gpa; //student gpa
};

#endif
