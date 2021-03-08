/* A program that stores information about students. 
   Users can commands to add a student, print existing students, delete a student, and quit the program.

   Date: 03.07.2021
   Author: Eliane Wang */


#include <iostream>
# include <cstring>
# include <vector>
# include <iomanip>

using namespace std;

struct Student {
  char firstname[10];
  char lastname[10];
  int id;
  float gpa;
};

void add(vector<Student*>* studentvector);
void print(vector<Student*>* studentvector);
void del(vector<Student*>* studentvector);
void quit(bool &running, vector<Student*>* studentvector);


int main() {
  
  char command[7];
  bool running = true;
  vector<Student*> *studentvector = new vector<Student*>();

  //evaluates users input and runs the command
  while (running == true) {
    cout << endl << "Commands: ADD, PRINT, DELETE, QUIT" << endl;
    cout << "Enter a command: " << endl;
    cin >> command;
    if (strcmp(command, "ADD") == 0) {
      add(studentvector);
    }
    else if (strcmp(command, "PRINT") == 0) {
      print(studentvector);
    }
    else if (strcmp(command, "DELETE") == 0) {
      del(studentvector);
    }
    else if (strcmp(command, "QUIT") == 0) {
      quit(running, studentvector);
    }
    else {
      cout << "your command was " << command;
      cout << "Invalid command. Please try again. " << endl;
    }
  }
}

//creates a new Student and adds to vector 
void add(vector<Student*>* studentvector) {
  cout << "your command was ADD" << endl;
  Student *studentpointer = new Student();
  cout << "First name?" << endl;
  cin >> studentpointer->firstname;
  cout << "Last name?" << endl;
  cin >> studentpointer->lastname;
  cout << "ID?" << endl;
  cin >> studentpointer->id;
  cout << "GPA?" << endl;
  cin >> studentpointer->gpa;
  studentvector->push_back(studentpointer);
}

//prints all Students currently stored
void print(vector<Student*>* studentvector) {
  cout << "your command was PRINT" << endl;
  for (auto studentpointer = studentvector->begin(); studentpointer < studentvector->end(); studentpointer++) {
    cout << (*studentpointer)->firstname << " " << (*studentpointer)->lastname << " ID: " << (*studentpointer)->id << fixed << setprecision(2) <<  " GPA: " << (*studentpointer)->gpa << endl;
  }
  
}

//removes Student from vector
void del(vector<Student*>* studentvector) {
  cout << "your command was DELETE" << endl;
  cout << "Student ID to delete: " << endl;
  int studentid;
  cin >> studentid;
  for (auto studentpointer = studentvector->begin(); studentpointer < studentvector->end(); studentpointer++) {
    if (((*studentpointer)->id) == studentid) {
      delete *studentpointer;
      studentvector->erase(studentpointer);
    }
  }

}

//exits program
void quit(bool &running, vector<Student*>* studentvector) {
  cout << "quitting..." << endl;
  running = false;
  for (auto studentpointer = studentvector->begin(); studentpointer < studentvector->end(); studentpointer++) {
    delete *studentpointer;
  }
  studentvector->clear();
  delete studentvector;
}
