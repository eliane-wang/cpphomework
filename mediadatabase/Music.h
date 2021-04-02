/* Music Class Header (Child)
   Contains 'duration', 'publisher', and 'artist' fields */

#include <iostream>
#include <string.h>

class Music: public Media {
 public:
  int getDuration();
  char* getArtist();
  char* getPublisher();
  char artist[20];
  int duration;
  char publisher[20];
};
