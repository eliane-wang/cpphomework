/* Media Class Header (Parent)
   Contains 'year', 'title', and 'media type' fields */

#include <iostream>
#include <string.h>
#include <vector>
#include <iomanip>

class Media {
 public:
  Media();
  int getYear();
  char* getTitle();
  char type[7];
  char title[20];
  int year;
  bool gamesType;
  bool musicType;
  bool moviesType;
};

