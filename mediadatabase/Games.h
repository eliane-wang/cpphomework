/*Games Class Header (Child)
  Contains 'publisher' and 'rating' fields */

#include <iostream>
#include <string.h>

class Games: public Media {
 public:
  int getRating();
  char* getPublisher();
  char publisher[20];
  int rating;
};
