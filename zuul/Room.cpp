/* Room Class
   Contains setters and getters for the room description, id, items, and exits */

#include <iostream>
#include <cstring>
#include <map>
#include "Room.h"

using namespace std;

Room::Room() {
}

//access the room description
char* Room::getDescription() {
  return description;
}

//set the room description
void Room::setDescription(char* newdescription) {
  description = newdescription;
}

//access the room id
int Room::getId() {
  return id;
}

//set the room id
void Room::setId(int newid) {
  id = newid;
}

//access the room item
int Room::getItem(){
  return item;
}

//set the room item
void Room::setItem(int newitem) {
  item = newitem;
}

//access the room exits
map<int, char*>* Room::getExits() {
  return &exits;
}

//set the room exits
void Room::setExits(map<int, char*> newexits) {
  exits = newexits;
}
