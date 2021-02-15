/* A simple guessing game. The computer picks a number between 0 and 100.
   The user makes a guess and is alerted if it is too high, low, or correct.
   If correct, it shows how many guesses you attempted and if you want to play again.
   
   Date: 02.14.2021
   Author: Eliane Wang */


#include <iostream>
using namespace std;

int main()
{
  int num = 10;
  int input = 0;
  bool correct = false;
  int guesses = 0;
  char yn;
  srand(time(NULL));
  int random = rand()%100;

  //game loops until the user is correct or game over
  while (correct == false) {
    cout << "Guess a number between 0 and 100: " << endl;
    guesses++;
    cin >> input;
    //guess is too low
    if (input < random){
      cout << "Your number is too low!" << endl;
    }
    //guess is too high
    else if (input > random ){
      cout << "Your number is too high!" << endl;
    }
    //guess is correct
    else {
      cout << "Your number is correct!" << endl;
      cout << "You guessed " << guesses << " times." << endl;
      cout << "Would you like to play again? y or n " << endl;
      cin >> yn;
      //user wants to play again
      if (yn == 'y') {
	correct = false;
	guesses = 0;
	random = rand()%100;
      }
      //user wants to play again
      else {
	correct = true;
	cout << "Game over. Thanks for playing!" << endl;
      }
    }
  }
}
