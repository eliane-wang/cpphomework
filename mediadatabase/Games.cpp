/* Games Class (Child)
   Contains methods to access 'rating' and 'publisher' fields */

# include <iostream>
#include "Media.h"
#include "Music.h"
#include "Movies.h"
#include "Games.h"

using namespace std;

//access 'rating' field
int Games::getRating() {
  return rating;
}

//access 'publisher' field
char* Games::getPublisher() {
  return publisher;
}
