/* A two-player tic-tac-toe game.
   Once the game is over the scoreboard is displayed. Players can play again, or end the game.

   Date: 02.27.2021
   Author: Eliane Wang */

#include <iostream>

using namespace std;

void drawBoard(char board[3][3], int column, int row, char player);
int rowNum(char row);
int columnNum(int column);
bool legalMove(char board[3][3], int column, int row);
bool checkWin(char board[3][3], char player);
void emptyBoard(char board[3][3]);
bool checkTie(char board[3][3]);

int main() {
  int number = 0;
  char board[3][3];
  int column = 1;
  char row = 'a';
  char player = 'X';
  bool running = true;
  char yn = 'y';
  int xWins = 0;
  int oWins = 0;
  
  emptyBoard(board);

  //while game is running
  while (running == true) {
    cout << "Player " << player << "'s turn" << endl;
    //enter a move
    cout << "enter a column #" << endl;
    cin >> column;
    cout << "enter a row letter" <<endl;
    cin >> row;
    //if move legal, make move
    if (legalMove(board, columnNum(column), rowNum(row)) == true) {
      drawBoard(board, columnNum(column), rowNum(row), player); //draw board
      //check for wins or ties
      if ((checkWin(board, player) == true) || (checkTie(board) == true)) {
	//if win, announce and tally wins
	if (checkWin(board, player) == true) {
       	  cout << "Player " << player << " has won the game!" << endl;
      	  if (player == 'X') {
	    xWins++;
	  }
	  else {
	    oWins++;
	  }
        }
	//if tie, announce
	else {
	  cout << "You tied!" << endl;
	}
	//display wins
	cout << "X wins: " << xWins << endl;
	cout << "O wins: " << oWins << endl;
	cout << "Would you like to play again? Enter 'y' or 'n'." << endl;
	cin >> yn;
	//play again
	if (yn == 'y') {
	  emptyBoard(board);
	  player = 'X';
	}
	//end game
	else {
	  cout << "Thanks for playing!" << endl;
	  running = false;
	}
      }
      //change player
      else {
        if (player == 'X') {
	  player = 'O';
        }
        else {
	  player = 'X';
        }
      }
    }
    //reprompt user if move is illegal
    else {
	  cout << "Your move is invalid! Please try again" << endl;
    }	  
  }


  return 0;
}

//create an empty board
void emptyBoard(char board[3][3]) {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      board[x][y] = ' ';
    }
  }
  cout << endl << '\t' << "  123" << endl;
  cout << '\t' << "a" << endl << '\t' << "b" << endl << '\t' << "c" << endl;
  cout << endl;
}

//draw the board
void drawBoard(char board[3][3], int column, int row, char player) {
  board[row][column] = player;
  cout << endl << '\t' << "  123" << endl;
  cout << '\t' << "a " << board[0][0] << board[0][1] << board[0][2] << endl;
  cout << '\t' << "b " << board[1][0] << board[1][1] << board[1][2] << endl;
  cout << '\t' << "c " << board[2][0] << board[2][1] << board[2][2] << endl;
  cout << endl;
  return;
}


//convert row input (a,b,c) into row range (0,1,2)
int rowNum(char row) {
  int num = 0;
  if (row == 'a') {
    num = 0;
  }
  else if (row == 'b') {
    num = 1;
  }
  else if (row == 'c') {
    num = 2;
  }
  return num;
}

//convert column input (1,2,3) to column range (0,1,2)
int columnNum(int column) {
  column = column - 1;
  return column;
}

//check if move is valid
bool legalMove(char board[3][3], int column, int row) {
  //if occupied, return false
  if (board[row][column] != ' ') {
    return false;
  }
  //if empty, return true
  else {
    return true;
  }
}


//check for tie
bool checkTie(char board[3][3]) {
  int counter = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (board[x][y] != ' ') {
	counter++;
      }
    }
  }
  if (counter == 9) {
    return true;
  }
  else {
    return false;
  }
}


//check for win
bool checkWin(char board[3][3], char player) {
  //row 0
  if ((board[0][0] == player) && (board[0][1] == player) && (board[0][2] == player)) {
    return true;
  }
  //row 1
  else if ((board[1][0] == player) && (board[1][1] == player) && (board[1][2] == player)) {
    return true;
  }
  //row 2
  else if ((board[2][0] == player) && (board[2][1] == player) && (board[2][2] == player)) {
    return true;
  }
  //column 0
  else if ((board[0][0] == player) && (board[1][0] == player) && (board[2][0] == player)) {
    return true;
  }
  //column 1
  else if ((board[0][1] == player) && (board[1][1] == player) && (board[2][1] == player)) {
    return true;
  }
  //column 2
  else if ((board[0][2] == player) && (board[1][2] == player) && (board[2][2] == player)) {
    return true;
  }
  //diagonal left to right
  else if ((board[0][0] == player) && (board[1][1] == player) && (board[2][2] == player)) {
    return true;
  }
  //diagonal right to left
  else if ((board[0][2] == player) && (board[1][1] == player) && (board[2][0] == player)) {
    return true;
  }
  //not a win
  else {
    return false;
  }
  
}


