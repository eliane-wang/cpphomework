/* Media Class (Parent)
   Contains methods to access 'year' and 'title' fields */

#include <iostream>
#include <string.h>
#include <vector>
#include <iomanip>

#include "Media.h"
#include "Music.h"
#include "Movies.h"
#include "Games.h"

using namespace std;

Media::Media() {
}

//access 'year' field
int Media::getYear() {
  return year;
}

//access 'title' field
char* Media::getTitle() {
  return title;
}
