/*Items Class
 Contains getters and setters for the item name and id*/
#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

Item::Item() {
}

//access item name
char* Item::getName() {
  return name;
}

//set item name
void Item::setName(char* newname) {
  name = newname;
}

//access item id
int Item::getId() {
  return id;
}

//set item id
void Item::setId(int newid) {
  id = newid;
}
