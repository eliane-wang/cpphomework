/* Movies Class Header (Child) 
   Contains 'director', 'duration', and 'rating' fields */

#include <iostream>
#include <string.h>

class Movies: public Media {
 public:
  int getRating();
  int getDuration();
  char* getDirector();
  char director[20];
  int duration;
  int rating;
  
};
