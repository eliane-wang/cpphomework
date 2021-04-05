/* Room Class Header 
   Contains getters and setters for the room description, id, items, and exits */
 
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

class Room {
 public:
  Room();
  char* getDescription();
  void setDescription(char*);
  int getId();
  void setId(int);
  void setItem(int);
  int getItem();
  map<int,char*>* getExits();
  void setExits(map<int,char*>);
 private:
  char* description;
  int id;
  int item;
  map<int,char*> exits;
};
