/* Music Class (Parent)
   Contains methods to access 'duration', 'artist', and 'publisher' fields */

#include <iostream>
#include "Media.h"
#include "Music.h"
#include "Movies.h"
#include "Games.h"

using namespace std;

//access 'duration' field
int Music::getDuration() {
  return duration;
}

//access 'artist' field
char* Music::getArtist() {
  return artist;
}

//access 'publisher' field
char* Music::getPublisher() {
  return publisher;
}
