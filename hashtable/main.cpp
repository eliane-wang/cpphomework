/* A program that uses a hash table to store information about students.
   Users can use the ADD, PRINT, DELETE, QUIT and AVERAGE commands.

   Date: 05.07.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include "hasht.h"

using namespace std;

void nameGen(int randfirst, int randlast, int idcount);

hasht HashT;

int main() {  
  char command[7];
  bool running = true;
  int idcount = 1;
  while (running == true) {
    cout << "Commands: ADD, PRINT, DELETE, QUIT" << endl;
    cin >> command;
    //ADD
    if (strcmp(command, "ADD") == 0) {
      cout << "Select a fill method: 'GENERATE' or 'MANUAL'?" << endl;
      cin >> command;
      if (strcmp(command, "GENERATE") == 0) { //randomly generates students
	int studentnum;
	srand(time(0));
	cout << "Generate how many students?" << endl;
	cin >> studentnum;
	int counter = 0;
	while (counter < studentnum) { //generates desired amount
	  int randfirst = rand()%19;
	  int randlast = rand()%19;
	  nameGen(randfirst, randlast, idcount);
	  counter ++;
	  idcount++; //increment id
	}
      }
      else if (strcmp(command, "MANUAL") == 0) { //user manually inputs student
	cout << "First name? " << endl;
	char* fname = new char[20];
	cin >> fname;
	cout << "Last name? " << endl;
	char* lname = new char[20];
	cin >> lname;
	cout << "Student ID: " << idcount << endl;
	cout << "Student GPA? " << endl;
	float newgpa;
	cin >> newgpa;
	HashT.add(fname, lname, idcount, newgpa); //adds to table
	idcount++; //increment id
      }
      else { //invalid
	cout << "Invalid command. " << endl;
      }
    }
    //PRINT
    else if (strcmp(command, "PRINT") == 0) {
      HashT.print();
    }
    //DELETE
    else if (strcmp(command, "DELETE") == 0) {
      cout << "Student id to delete: " << endl;
      int newid;
      cin >> newid;
      HashT.del(newid);
    }
    //QUIT
    else if (strcmp(command, "QUIT") == 0) {
      running = false;
    }
    //INVALID
    else {
      cout << "Invalid command! Try again. " << endl;
    }
    cout << endl;
  }
}


//randomly generates student name, id, an gpa 
void nameGen(int randfirst, int randlast, int idcount) {
  char* first = new char[15];
  char* last = new char[15];
  ifstream firstname("firstnames.txt"); //first name file
  ifstream lastname("lastnames.txt"); //last name file
  float gpa = (float)(rand()%500)/100; //random gpa
  int x = 0;
  firstname >> first;
  while (x != randfirst) { //grabs first name
    firstname >> first;
    x++;
  }
  x = 0;
  lastname >> last;
  while (x != randlast) { //grabs last name
    lastname >> last;
    x++;
  }
  HashT.add(first, last, idcount, gpa);
  //print student
  cout << first << " " << last << " id: " << idcount << " gpa: " << fixed << setprecision(2) << gpa << endl;  
}

