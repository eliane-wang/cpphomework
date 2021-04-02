/* A database that tracks information about video games, music, and movies.
   Each media type stores fields such as the title and year.
   Users can use the ADD, SEARCH, DELETE, and QUIT commands.

   Date: 04.01.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

#include "Media.h"
#include "Music.h"
#include "Movies.h"
#include "Games.h"

using namespace std;

//function prototypes
void add(vector<Media*> *mediavector);
void search(vector<Media*> *mediavector);
void del(vector<Media*> *mediavector);
void quit(bool &running, vector<Media*>* mediavector);

//main
int main() {
  char command[7];
  bool running = true;
  vector<Media*> *mediavector = new vector<Media*>();
  //evaluates user input and runs the command
  while (running == true) {
    cout << endl << "Commands: ADD, SEARCH, DELETE, QUIT" << endl;
    cout << "Enter a command: " << endl;
    cin >> command;
    //ADD command
    if (strcmp(command, "ADD") == 0) {
      add(mediavector);
    }
    //SEARCH command
    else if (strcmp(command, "SEARCH") == 0) {
      search(mediavector);
    }
    //DELETE command
    else if (strcmp(command, "DELETE") == 0) {
      del(mediavector);
    }
    //QUIT command
    else if (strcmp(command, "QUIT") == 0) {
      quit(running, mediavector);
    }
    //invalid command
    else {
      cout << "You entered: " << command << endl;
      cout << "Invalid command. Please try again. " << endl;
    }
  }
}

//adds information to each kind of media, and the information in each field
void add(vector<Media*> *mediavector) {
  cout << "Command used: ADD" << endl;
  cout << "What media type? Enter '1' for 'Games', '2' for 'Music', or '3' for 'Movies'" << endl;
  int num;
  cin >> num;
  //Games
  if (num == 1) {
    Games* gamesptr = new Games();
    gamesptr->gamesType = true;
    gamesptr->musicType = false;
    gamesptr->moviesType = false;
    //user enters information
    cout << "Title?" << endl;
    cin.ignore();
    cin.getline(gamesptr->title, 20);
    cout << "Year?" << endl;
    cin >> gamesptr->year;
    cout << "Publisher?" << endl;
    cin.ignore();
    cin.getline(gamesptr->publisher, 20);
    cout << "Rating?" << endl;
    cin >> gamesptr->rating;
    //displays added information
    cout << "Title: " << (gamesptr->getTitle());
    cout << " Year: " << (gamesptr->getYear());
    cout << " Publisher: " << (gamesptr->getPublisher());
    cout << " Rating: " << (gamesptr->getRating()) << endl;
    mediavector->push_back(gamesptr); //adds to vector
    }
  
  //Music
  if (num == 2) {
    Music* musicptr = new Music();
    musicptr->gamesType = false;
    musicptr->musicType = true;
    musicptr->moviesType = false;
    //user enters information
    cout << "Title?" << endl;
    cin.ignore();
    cin.getline(musicptr->title, 20);
    cout << "Artist?" << endl;
    cin.getline(musicptr->artist, 20);
    cout << "Year?" << endl;
    cin >> musicptr->year;
    cout << "Duration (min)?" << endl;
    cin >> musicptr->duration;
    cout << "Publisher?" << endl;
    cin.ignore();
    cin.getline(musicptr->publisher, 20);
    //displays information
    cout << "Title: " << (musicptr->getTitle());
    cout << " Year: " << (musicptr->getYear());
    cout << " Artist: " << (musicptr->getArtist());
    cout << " Duration (min): " << (musicptr->getDuration());
    cout << " Publisher: " << (musicptr->getPublisher()) << endl;
    mediavector->push_back(musicptr); //adds to vector
    
  }
  //Movies
  if (num == 3) {
    Movies* moviesptr = new Movies();    
    moviesptr->gamesType = false;
    moviesptr->musicType = false;
    moviesptr->moviesType = true;
    //user enters information
    cout << "Title?" << endl;
    cin.ignore();
    cin.getline(moviesptr->title, 20);
    cout << "Director?" << endl;
    cin.getline(moviesptr->director, 20);
    cout << "Year?" << endl;
    cin >> moviesptr->year;
    cout << "Duration (min)?" << endl;
    cin >> moviesptr->duration;
    cout << "Rating?" << endl;
    cin >> moviesptr->rating;
    //displays information
    cout << "Title: " << (moviesptr->getTitle());
    cout << " Year: " << (moviesptr->getYear());
    cout << " Director: " << (moviesptr->getDirector());
    cout << " Rating: " << (moviesptr->getRating());
    cout << " Duration (min): " << (moviesptr->getDuration()) << endl;
    mediavector->push_back(moviesptr); //adds to vector
  }
}

//search and print information in the database by the title or year
void search(vector<Media*> *mediavector) {
  int msg;
  cout << "Enter '1' to search by title or '2' to search by year" << endl;
  cin >> msg;
  char titleInput[20];
  int yearInput;
  //searching by title
  if (msg == 1) {
    cout << "What is the title?" << endl;
    cin.ignore();
    cin.getline(titleInput, 20);
  }
  //searching by year
  if (msg == 2) {
    cout << "What is the year?" << endl;
    cin >> yearInput;
  }
  //iterates through each object in the database
  for (auto mediapointer =mediavector->begin(); mediapointer < mediavector->end(); mediapointer++) {
    if ((strcmp(titleInput, (*mediapointer)->getTitle()) == 0) || ((*mediapointer)->getYear() == yearInput)) { //if title or year match
      //print games media type
      if ((*mediapointer)->gamesType == true) {
	Games* gamesptr = static_cast<Games*>(*mediapointer);
	cout << "Title: " << (gamesptr->getTitle());
	cout << " Year: " << (gamesptr->getYear());
	cout << " Publisher: " << (gamesptr->getPublisher());
	cout << " Rating: " << (gamesptr->getRating()) << endl;
      
      }
      //print music media type
      if ((*mediapointer)->musicType == true) {
	Music* musicptr = static_cast<Music*>(*mediapointer);
	cout << "Title: " << (musicptr->getTitle());
	cout << " Year: " << (musicptr->getYear());
	cout << " Artist: " << (musicptr->getArtist());
	cout << " Duration (min): " << (musicptr->getDuration());
	cout << " Publisher: " << (musicptr->getPublisher()) << endl;
      }
      //print movies media type
      if ((*mediapointer)->moviesType == true) {
	Movies* moviesptr = static_cast<Movies*>(*mediapointer);
	cout << "Title: " << (moviesptr->getTitle());
	cout << " Year: " << (moviesptr->getYear());
	cout << " Director: " << (moviesptr->getDirector());
	cout << " Rating: " << (moviesptr->getRating());
	cout << " Duration (min): " << (moviesptr->getDuration()) << endl;
      }
    }
    
  
  }
}

//delete an item by title or year
void del(vector<Media*> *mediavector) {
  int msg;
  cout << "Enter '1' to delete by title or '2' to search by year" << endl;
  cin >> msg;
  char titleInput[20];
  int yearInput;
  //deleting by title
  if (msg == 1) {
    cout << "What is the title?" << endl;
    cin.ignore();
    cin.getline(titleInput, 20);
  }
  //deleting by year
  if (msg == 2) {
    cout << "What is the year?" << endl;
    cin >> yearInput;
  }
  //iterates through each object in the database
    for (auto mediapointer =mediavector->begin(); mediapointer < mediavector->end(); mediapointer++) {
      if ((strcmp(titleInput, (*mediapointer)->getTitle()) == 0) || ((*mediapointer)->getYear()==yearInput)) { //if title or year match
	//games
	if ((*mediapointer)->gamesType == true) {
	  Games* gamesptr = static_cast<Games*>(*mediapointer);
	  //confirm delete
	  cout << "Are you sure you want to delete " << gamesptr->getTitle() << " ? 'y' or 'n'" << endl;
	  char yn;
	  cin >> yn;
	  if (yn == 'y') {
	    cout << "Deleting : " << gamesptr->getTitle() << endl;
	    //deletes
	    delete gamesptr;
	    mediavector->erase(mediapointer);
	  }
	}
	//music
	else if((*mediapointer)->musicType == true) {
	  Music* musicptr = static_cast<Music*>(*mediapointer);
	   //confirm delete
          cout << "Are you sure you want to delete " << musicptr->getTitle() << " ? 'y' or 'n'" << endl;
	  char yn;
	  cin >> yn;
	  if (yn == 'y') {
	    cout << "Deleting: " << musicptr->getTitle() << endl;
	    //deletes
	    delete musicptr;
	    mediavector->erase(mediapointer);
	  }
	}
	//movies
	else if ((*mediapointer)->moviesType == true) {
	  Movies* moviesptr = static_cast<Movies*>(*mediapointer);
	  //confirm delete
	  cout << "Are you sure you want to delete " << moviesptr->getTitle()<< " ? 'y' or 'n'" << endl;
	  char yn;
	  cin >> yn;
	  if (yn == 'y') {
	    cout << "Deleting: " << moviesptr->getTitle() << endl;
	    //deletes
	    delete moviesptr;
	    mediavector->erase(mediapointer);
	  }
	}
      }
    }
}

//quits the program
void quit (bool &running, vector<Media*>* mediavector) {
  cout << "Command used: QUIT" << endl;
  running = false;
  //deleting objects
  for (auto mediapointer = mediavector->begin(); mediapointer < mediavector->end(); mediapointer++) {
    delete *mediapointer;
  }
  mediavector->clear();
  delete mediavector;
}
