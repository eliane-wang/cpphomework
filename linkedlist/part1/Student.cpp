/*Student Class 
 Students have a first name, last name, ID, and GPA */

#include <iostream>
#include "Student.h"

using namespace std;

//constructor
Student::Student(char* fname, char* lname, int newid, float newgpa) {
  firstname = fname;
  lastname = lname;
  id = newid;
  gpa = newgpa;
}

//get student first name
char* Student::getFirstName() {
  return firstname;
}

//get student last name
char* Student::getLastName() {
  return lastname;
}

//get student id
int Student::getId() {
  return id;
}

//get student gpa
float Student::getGpa() {
  return gpa;
}


