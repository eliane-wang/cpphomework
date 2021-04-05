/* A text-based adventure game involving navigating between rooms, and picking up items.
   Players use the MOVE, GRAB, DROP, INVENTORY, QUIT commands.
   The objective of the game is to escape the fire.

   Date: 04.04.2021
   Author: Eliane Wang */


#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <map>
#include "Room.h"
#include "Item.h"

using namespace std;


//function prototypes
void printCurrentRoom(vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom);
int move (vector<Room*>* roomvector, char direction[], int currentRoom);
void grab(vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom, vector<int>*inventory, char itemName[]);
void showInventory(vector<Item*>* itemvector, vector<int> inventory);
void drop(vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom, vector<int>*inve\
ntory, char itemName[]);

int main() {
  char command[10];
  bool running = true;
  int currentRoom = 0;

  //vectors
  vector <Room*> *roomvector = new vector<Room*>();
  vector <Item*> *itemvector = new vector<Item*>();
  vector <int> inventory;
  map <int,char*> mymap;

  //zuul prompt
  cout << "You wake up the the deafening sound of the fire alarm." << endl;
  cout << "Your house is on fire! Quickly collect your valuables and escape." << endl;
  cout << endl;
  
  //initialize rooms
  //bedroom
  Room* bedroom = new Room();
  bedroom->setDescription((char*)("You are in the bedroom. Let's get out of here first."));
  bedroom->setId(0);
  bedroom->setItem(0);
  mymap.insert(pair<int,char*>(1, (char*)("NORTH"))); //stairs
  mymap.insert(pair<int,char*>(3, (char*)("EAST"))); //closet
  mymap.insert(pair<int,char*>(7, (char*)("SOUTH"))); //living room
  mymap.insert(pair<int,char*>(6, (char*)("WEST"))); //bathroom
  bedroom->setExits(mymap);
  roomvector->push_back(bedroom);
  mymap.clear();

  //stairs
  Room* stairs = new Room();
  stairs->setDescription((char*)("You are on the stairs. The heat seems to be coming from upstairs (NORTH)...you probably don't want to go there."));
  stairs->setId(1);
  stairs->setItem(5); //no item
  mymap.insert(pair<int,char*>(2, (char*)("NORTH"))); //attic
  mymap.insert(pair<int,char*>(0, (char*)("SOUTH"))); //bedroom
  stairs->setExits(mymap);
  roomvector->push_back(stairs);
  mymap.clear();

  //attic
  Room* attic = new Room();
  attic->setDescription((char*)("You are on the attic."));
  attic->setId(2);
  attic->setItem(5); //no item
  mymap.insert(pair<int,char*>(1, (char*)("SOUTH"))); //stairs
  attic->setExits(mymap);
  roomvector->push_back(attic);
  mymap.clear();

  //closet
  Room* closet = new Room();
  closet->setDescription((char*)("You are in the closet. You hear the wails of an infant...right, you might want to rescue your baby sibling. Was it coming from the nursery?"));
  closet->setId(3);
  closet->setItem(5); //no item
  mymap.insert(pair<int,char*>(5, (char*)("NORTH"))); //laundry
  mymap.insert(pair<int,char*>(4, (char*)("EAST"))); //nursery
  mymap.insert(pair<int,char*>(0, (char*)("WEST"))); //bedroom
  closet->setExits(mymap);
  roomvector->push_back(closet);
  mymap.clear();

  //nursery
  Room* nursery = new Room();
  nursery->setDescription((char*)("You are in the nursery. It looks unusually eerie in here."));
  nursery->setId(4);
  nursery->setItem(1);
  mymap.insert(pair<int,char*>(3, (char*)("WEST"))); //closet
  nursery->setExits(mymap);
  roomvector->push_back(nursery);
  mymap.clear();

  //laundry
  Room* laundry = new Room();
  laundry->setDescription((char*)("You are in the laundry room. (I won't be doing that any time soon...)"));
  laundry->setId(5);
  laundry->setItem(5); //no item
  mymap.insert(pair<int,char*>(3, (char*)("SOUTH"))); //closet
  laundry->setExits(mymap);
  roomvector->push_back(laundry);
  mymap.clear();

  //bathroom
  Room* bathroom = new Room();
  bathroom->setDescription((char*)("You are in the bathroom. The mirror is fogged up."));
  bathroom->setId(6);
  bathroom->setItem(5); //no item
  mymap.insert(pair<int,char*>(0, (char*)("EAST"))); //bedroom
  bathroom->setExits(mymap);
  roomvector->push_back(bathroom);
  mymap.clear();

  //living room
  Room* living = new Room();
  living->setDescription((char*)("You are in the living room (Better get out before it becomes a death room)."));
  living->setId(7);
  living->setItem(5); //no item
  mymap.insert(pair<int,char*>(0, (char*)("NORTH"))); //bedroom
  mymap.insert(pair<int,char*>(8, (char*)("EAST"))); //kitchen
  mymap.insert(pair<int,char*>(13, (char*)("SOUTH"))); //garage
  mymap.insert(pair<int,char*>(11, (char*)("WEST"))); //study
  living->setExits(mymap);
  roomvector->push_back(living);
  mymap.clear();

  //kitchen
  Room* kitchen = new Room();
  kitchen->setDescription((char*)("You are in the kitchen. It sure does smell like burnt cookies..."));
  kitchen->setId(8);
  kitchen->setItem(3);
  mymap.insert(pair<int,char*>(9, (char*)("EAST"))); //dining
  mymap.insert(pair<int,char*>(10, (char*)("SOUTH"))); //pantry
  mymap.insert(pair<int,char*>(7, (char*)("WEST"))); //living
  kitchen->setExits(mymap);
  roomvector->push_back(kitchen);
  mymap.clear();

  //dining room
  Room* dining = new Room();
  dining->setDescription((char*)("You are in the dining room. Your stomach growls at the thought of food."));
  dining->setId(9);
  dining->setItem(5); //no item
  mymap.insert(pair<int,char*>(8, (char*)("WEST"))); //kitchen
  dining->setExits(mymap);
  roomvector->push_back(dining);
  mymap.clear();

  //pantry
  Room* pantry = new Room();
  pantry->setDescription((char*)("You are in the pantry. Everything is burnt..."));
  pantry->setId(10);
  pantry->setItem(5); //no item
  mymap.insert(pair<int,char*>(8, (char*)("NORTH"))); //kitchen
  pantry->setExits(mymap);
  roomvector->push_back(pantry);
  mymap.clear();

  //study
  Room* study = new Room();
  study->setDescription((char*)("You are in the study. Don't think you can turn in that overdue math assignment anymore..."));
  study->setId(11);
  study->setItem(2);
  mymap.insert(pair<int,char*>(7, (char*)("EAST"))); //living
  mymap.insert(pair<int,char*>(12, (char*)("SOUTH"))); //game
  study->setExits(mymap);
  roomvector->push_back(study);
  mymap.clear();

  //game room
  Room* game = new Room();
  game->setDescription((char*)("You are in the game room. You shouldn't be playing around though."));
  game->setId(12);
  game->setItem(5); //no item
  mymap.insert(pair<int,char*>(11, (char*)("NORTH"))); //study
  game->setExits(mymap);
  roomvector->push_back(game);
  mymap.clear();

  //garage
  Room* garage = new Room();
  garage->setDescription((char*)("You are in the garage. Escape is close..."));
  garage->setId(13);
  garage->setItem(5); //no item
  mymap.insert(pair<int,char*>(7, (char*)("NORTH"))); //living
  mymap.insert(pair<int,char*>(14, (char*)("EAST"))); //basement
  mymap.insert(pair<int,char*>(15, (char*)("SOUTH"))); //exit
  garage->setExits(mymap);
  roomvector->push_back(garage);
  mymap.clear();

  //basement
  Room* basement = new Room();
  basement->setDescription((char*)("You are in the basement. It's somehow 10x scarier than normal."));
  basement->setId(14);
  basement->setItem(4);
  mymap.insert(pair<int,char*>(13, (char*)("WEST"))); //garage
  basement->setExits(mymap);
  roomvector->push_back(basement);
  mymap.clear();

  //exit
  Room* exit = new Room();
  exit->setDescription((char*)("You made it to the exit!"));
  exit->setId(15);
  exit->setItem(5); //no item
  mymap.insert(pair<int,char*>(13, (char*)("NORTH"))); //garage
  exit->setExits(mymap);
  roomvector->push_back(exit);
  mymap.clear();

  //initialize items
  //phone
  Item* phone = new Item();
  phone->setName((char*)("PHONE"));
  phone->setId(0);
  itemvector->push_back(phone);

  //baby
  Item* baby = new Item();
  baby->setName((char*)("BABY"));
  baby->setId(1);
  itemvector->push_back(baby);

  //homework
  Item* homework = new Item();
  homework->setName((char*)("HOMEWORK"));
  homework->setId(2);
  itemvector->push_back(homework);

  //snack
  Item* snack = new Item();
  snack->setName((char*)("SNACK"));
  snack->setId(3);
  itemvector->push_back(snack);

  //extinguisher
  Item* extinguisher = new Item();
  extinguisher->setName((char*)("EXTINGUISHER"));
  extinguisher->setId(4);
  itemvector->push_back(extinguisher);

  //while user is playing
  while (running == true) {
    printCurrentRoom(roomvector, itemvector, currentRoom);    
    cout << "Commands:\tMOVE\tINVENTORY\tGRAB\tDROP\tQUIT" << endl;
    cin >> command;
    //MOVE command
    if (strcmp(command, "MOVE") == 0) {
      cout << "Direction to move:" << endl;
      char direction[6];
      cin >> direction;
      //move rooms
      if (move (roomvector, direction, currentRoom) != 16) { //if move is valid
	cout << "moving..." << endl;
	currentRoom = move (roomvector, direction, currentRoom);
      }
      //invalid move
      else {
	cout << "You can't move there." << endl;
      }
    }
    //INVENTORY command
    else if (strcmp(command, "INVENTORY") == 0) {
      cout << "opening inventory..." << endl;
      showInventory(itemvector,inventory);
    }
    //GRAB command
    else if (strcmp(command, "GRAB") == 0) {
      cout << "Item to pick up: " << endl;
      char itemName[13];
      cin >> itemName;
      grab(roomvector,itemvector,currentRoom,&inventory,itemName);
    }
    //DROP command
    else if (strcmp(command, "DROP") == 0) {
      //cout << "dropping..." << endl;
      cout << "Item to drop: " << endl;
      char itemName[13];
      cin >> itemName;
      drop(roomvector,itemvector,currentRoom,&inventory,itemName);

    }
    //QUIT command
    else if (strcmp(command, "QUIT") == 0) {
      cout << "quitting..." << endl;
      running = false;
    }
    //invalid command
    else {
      cout << "Invalid command. Please try again." << endl;
    }
    cout << endl;
    
    //player won (found the exit)
    if (currentRoom == 15) {
      cout << "Congrats, you escaped the fire!" << endl;
      int winCounter = 0;
      //check if baby was saved
      for (int i = 0; i < inventory.size(); i++) {
	if (inventory[i] == 1) {
	  winCounter++;
	}
      }
      //baby was not rescued
      if (winCounter == 0) {
	cout << "(though you probably should've saved your baby sibling)" << endl;
      }
      //baby rescued
      else {
	cout << "You managed to save your sibling too." << endl;
      }
      running = false;
    }
    //player lost (moved to attic, dropped the baby, or grabbed the wrong items)
    if (currentRoom == 2) {
      cout << "The flame engulfs you, and you succumb to the fire." << endl;
      running = false;
    }
    //grabbed wrong items (snack and homework)
    for (int i = 0; i < inventory.size(); i++) {
      if ((inventory[i] == 2) || (inventory[i] == 3)) {
	cout << "Your hands were too full...did you really need this?" << endl;
	cout << "You collapse and succumb to the flames." << endl;
	cout << "Don't be so greedy next time."<< endl;
	running = false;
        }
      }

    
  }
  cout << "GAME OVER" << endl;
}


//prints the room the player is currently in, as well as the items and exits
void printCurrentRoom (vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom) {
  //iterates through room in the vector
 for (auto roomptr = roomvector->begin(); roomptr < roomvector->end(); roomptr++) {
   if ((*roomptr)->getId() == currentRoom) { //current room
     cout << (*roomptr)->getDescription() << endl;
     int itemCount = 0;
     //iterates through each object in the vector
     for (auto itemptr = itemvector->begin(); itemptr < itemvector->end(); itemptr++) {
       //output items in the room
       if ((*roomptr)->getItem() == (*itemptr)->getId()) {
	 cout << "There is a/n " << (*itemptr)->getName() << " here (though you should only grab the necessities...)" << endl;
	 itemCount++;
       }
     }
     //no items
     if (itemCount == 0) {
       cout << "There isn't much to see here..." << endl;
     }
     //outputs exits
     cout << "There are exits: ";
     for (auto it = (*roomptr)->getExits()->begin(); it != (*roomptr)->getExits()->end(); it++) {
       cout << it->second << " " ;
     }     
     cout << endl;
   }
 }
}

//returns the ID of the new room
int move (vector<Room*>* roomvector, char direction[], int currentRoom) {
  //iterates through the rooms
  for (auto roomptr = roomvector->begin(); roomptr < roomvector->end(); roomptr++) {
   if ((*roomptr)->getId() == currentRoom) { //current room
     //iterates through the exits
     for (auto it = (*roomptr)->getExits()->begin(); it != (*roomptr)->getExits()->end(); it++) {
       if (strcmp(it->second, direction) == 0) {
	 return it->first; //return id of new room
       }
     }
   }
 }
  return 16; //invalid room id
}

//grabs an item from room, add it to inventory
void grab(vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom, vector<int>*inventory, char itemName[]) {
  int counter = 0;
 for (auto roomptr = roomvector->begin(); roomptr < roomvector->end(); roomptr++) {
   if ((*roomptr)->getId() == currentRoom) { //current room
     for (auto itemptr = itemvector->begin(); itemptr < itemvector->end(); itemptr++) {
       if (((*roomptr)->getItem() == (*itemptr)->getId()) && (strcmp(itemName, (*itemptr)->getName())) == 0) { //items match
	   inventory->push_back((*itemptr)->getId());
	   (*roomptr)->setItem(5); //clear item from room
	   cout << "Grabbed the " << (*itemptr)->getName() << endl;
	   counter++;
       }
     }
   }
 }
 //invalid item name
 if (counter == 0) {
   cout << "You can't pick that up." << endl;
 }
}

//drops an item from room, removes it from inventory
void drop(vector<Room*>* roomvector, vector<Item*>* itemvector, int currentRoom, vector<int>*inve\
ntory, char itemName[]) {
  int counter = 0;
  for (auto roomptr = roomvector->begin(); roomptr < roomvector->end(); roomptr++) {
   if ((*roomptr)->getId() == currentRoom) { //current room
     if ((*roomptr)->getItem() == 5) { //no items
        for (auto itemptr = itemvector->begin(); itemptr < itemvector->end(); itemptr++) {
	  if (strcmp((*itemptr)->getName(), itemName) == 0) { //if item in inventory
	    for (auto inventoryptr = inventory->begin(); inventoryptr != inventory->end(); inventoryptr++) {
	      //check inventory for item
	      if ((*itemptr)->getId() == (*inventoryptr)) {
		cout << "Dropped " << (*itemptr)->getName() << endl; 
		(*roomptr)->setItem((*itemptr)->getId()); //add item to room
		inventoryptr = inventory->erase(inventoryptr); //remove from inventory
		counter++;
		return;
	      }
	    }
	  }
	} 
	 
     }
   }
  }
  //invalid item
  if (counter == 0) {
    cout << "Unable to drop item. The room is too full, or the item does not exist." << endl;
  }
}

//prints the player inventory
void showInventory(vector<Item*>* itemvector, vector<int> inventory) {
  cout << "You have";
  int counter = 0;
  //iterate through items and inventory
  for (auto itemptr = itemvector->begin(); itemptr < itemvector->end(); itemptr++) {
    for (int i = 0; i < inventory.size(); i++) {
      //item in inventory
      if ((*itemptr)->getId() == inventory[i]) {
	cout << " " << (*itemptr)->getName(); //prints
	counter++;
      }
    }
  }
  //inventory emtpy
  if (counter == 0) {
    cout << " nothing.";
  }
  cout << endl;
}
