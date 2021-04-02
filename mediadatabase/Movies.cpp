/* Movies Class (Parent)
   Contains methods to access 'rating', 'duration', and 'director' fields*/

#include <iostream>
#include "Media.h"
#include "Music.h"
#include "Movies.h"
#include "Games.h"

using namespace std;

//access 'rating' field
int Movies::getRating() {
  return rating;
}

//access 'duration' field
int Movies::getDuration() {
  return duration;
}

//access 'director' field
char* Movies::getDirector() {
  return director;
}


