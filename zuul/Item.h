/* Items Class Header
   Contains getters and setters for the item name and id */

#include <iostream>
#include <cstring>

using namespace std;

class Item {
 public:
  Item();
  char* getName();
  void setName(char*);
  int getId();
  void setId(int);
 private:
  char* name;
  int id;
};
