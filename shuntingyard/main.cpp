/* The program converts an expression from infix to postfix notation using the shunting yard algorithm.
   Using an expression tree created from the postfix notation, users can output the expression as an infix, prefix, or postfix notation. 

   References: https://www.youtube.com/watch?v=Wz85Hiwi5MY
               https://www.youtube.com/watch?v=jos1Flt21is

   Date: 12.23.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//node struct for linked list 
struct token {
  char data;
  token* next;
  token(char newdata) {
    data = newdata;
    next = NULL;
  }
};

void enqueue(token* &front, char data);
void dequeue(token* &front);
void push(token* &top, char data);
char peek(token* top);
void pop(token* &top);
void print(token* head);

int main() {
  char input[20];
  token* front = NULL; //head of linked list for queue
  token* top = NULL; //head of linked list for stack
  
  cout << "Shunting Yard Program" << endl;
  cout << "Enter an expression in infix notation, separating each token with a space." << endl;
  cin.get(input, 20);
  cin.get();
  cout << "Expression entered: " << input << endl;

  for (int i = 0; i < strlen(input); i++) { //iterate through each token
    if (input[i] != ' ') {
      
      
    }
  }
  print  
}

//inserts token to rear in queue
void enqueue(token* &front, char data) {
  if (front != NULL) {
    enqueue(front->next, data);
  }
  else {
    front = new token(data);
  }
}

//removes the front token from queue
void dequeue(token* &front){
  token* del = front->next;
  delete(front);
  front = del;
}

//inserts token to top of stack
void push(token* &top, char data) {
  token* temp = new token(data);
  temp->next = top;
  top = temp;
}

//removes token from top of stack
void pop(token* &top) {
  token* temp = top;
  top = top->next;
  delete(temp);
}

//retrieves token top of stack
char peek(token* top) {
  return top->data;
}

void print(token* head) {
  if (head != NULL) {
    cout << "token: " << head->data << endl;
    print(head->next);
  }
}






