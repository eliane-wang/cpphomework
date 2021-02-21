/* Palindrome checker. The user enters a message and the computer determines whether it is a palindrome
   (a sequence that reads the same backward as forward). 
   
   Date: 02.21.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>

using namespace std;

int main() {
  //user inputs str
  char str[81];
  cout << "write something: " << endl;
  cin.get(str, 81);
  cin.get();
  
  //convert str to lowercase
  for (int i = 0; i < str[i] != '\0'; i++) {
    str[i] = tolower(str[i]);
  }

  //check for palindrome by comparing first and last letter
  bool palindrome = true;
  int j = strlen(str); //counts from last letter
  for (int i = 0; i < strlen(str); i++) {
    j--;
    while ((isalpha(str[i]) == false) && i < strlen(str)) { //skips for whitespace or punctuation
      i++;
    }
    while ((isalpha(str[j]) == false) && j > 0) { //skips for whitespace or punctuation
      j--;
    }
    //check for matching characters
    if (!(str[i] == str[j])) {
      palindrome = false;
    }
  }
  
  //output result
  if (palindrome == true) {
    cout << "Palindrome." << endl;
  }
  else {
    cout << "Not a palindrome." << endl;
  }

  return 0;
}
