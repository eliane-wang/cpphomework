//main

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
  /* testing stuff*/
  char fn[20] = "kylie";
  char* f = new char[20];
  memcpy(f, fn, strlen(fn));
  HashT.add(f, (char*)("jenner"), 1, 4.0);
  HashT.print();
  HashT.del(f);
  cout << endl;
  /*==============================*/
  
  char command[7];
  bool running = true;
  int idcount = 1;
  while (running == true) {
    cout << "Commands: ADD, PRINT, DELETE, QUIT" << endl;
    cin >> command;
    //ADD
    if (strcmp(command, "ADD") == 0) {
      //randomly generate students
      int studentnum;
      srand(time(0));
      cout << "generate how many students?" << endl;
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
    //PRINT
    else if (strcmp(command, "PRINT") == 0) {
      HashT.print();
    }
    //DELETE
    else if (strcmp(command, "DELETE") == 0) {
      cout << "Student (first) name to delete: " << endl;
      char* fname = new char[20];
      cin >> fname;
      HashT.del(fname);
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
  char first[15];
  char last[15];
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
  //add student to hash table
  char* fname = new char[20];
  char* lname = new char[20];
  memcpy(fname, first, strlen(first));
  memcpy(lname, last, strlen(last));
  HashT.add(fname, lname, idcount, gpa);
  //print student
  cout << first << " " << last;
  cout << " id: " << idcount;
  cout << " gpa: " << fixed << setprecision(2) << gpa << endl;
  
}

