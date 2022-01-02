/* The program converts an expression from infix to postfix notation using the shunting yard algorithm.
   Using an expression tree created from the postfix notation, users can output the expression as an infix, prefix, or postfix notation.

   References: https://www.youtube.com/watch?v=Wz85Hiwi5MY
               https://www.youtube.com/watch?v=jos1Flt21is
               https://en.wikipedia.org/wiki/Shunting-yard_algorithm
               https://www.krivalar.com/data-structures-expression-tree

   Date: 12.25.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>

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

//class for binary expresssion tree nodes
class tree {
  public:
    token* data;
    tree* left;
    tree* right;
    tree* next;
    tree(token* newdata) {
      data = newdata;
      left = NULL;
      right = NULL;
      next = NULL;
    }
};

tree* build(token* front);
void prefix(tree* root);
void infix(tree* root);
void postfix(tree* root);
void enqueue(token* &front, char data);
void dequeue(token* &front);
void push(token* &top, char data);
char peek(token* top);
void pushTree(tree* &top, tree* data);
void popTree(tree* &top);
void pop(token* &top);
void print(token* head);
int precedence(char op/*erator*/);

int main() {
  char input[100];
  token* front = NULL; //head of linked list for queue
  token* top = NULL; //head of linked list for stack

  cout << "Shunting Yard Program" << endl;
  cout << "Enter an expression in infix notation (including parentheses), separating each token with a space." << endl;
  cin.get(input, 100);
  cin.get();


  for (int i = 0; i < strlen(input); i++) { //iterate through each token
    if (input[i] != ' ') {
      if (isdigit(input[i])) { //if digit, queue 
        enqueue(front, input[i]);
      }
      
      else if (input[i] == '(') { //if open parenthesis, push to stack
        push(top, input[i]);  
      }
      else if (input[i] == ')') { //if close parenthesis
        while (top != NULL && peek(top) != '(') { //while top of stack is not an open parenthesis, pop token from stack and queue
          enqueue(front, peek(top));
          pop(top);
        }
        pop(top); //pop open parenthesis
      }
      else if (precedence(input[i]) != 0) { //if operator
        while ((top != NULL) && 
        ((precedence(peek(top)) > precedence(input[i])) || /* operator on top has greater precedence */ ((precedence(peek(top)) == precedence(input[i])) && input[i] != '^')) && /* operator on top has same precedence and is right associative */ (peek(top) != '(')) { //pop operator from stack and queue
          enqueue(front, peek(top)); 
          pop(top);
        } 
        push(top, input[i]); //push operator onto stack
      }
      cout << endl;
    }
  } 
  while (top != NULL && !isdigit(peek(top)) && peek(top) != '(') { //while there are operators on the stack    
    enqueue(front, peek(top)); //pop operator from stack and queue
    pop(top);
  }
  tree* root = NULL; //root of binary expression tree
  root = build(front); //builds from output  queue
  cout << "Output as PREFIX, INFIX, or POSTFIX? " << endl;
  cin.get(input, 100);
  cin.get();
  if (strcmp(input, "PREFIX") == 0) { //prefix notation
    prefix(root);
  }
  else if (strcmp(input, "INFIX") == 0) { //infix notation
    infix(root);
  }
  else if (strcmp(input, "POSTFIX") == 0) { //postfix notation
    postfix(root);
  }
  else { //invalid
    cout << "Invalid command. ";
  }
}

//constructs binary expression tree from postfix notation
tree* build(token* front) {
  tree* treestack;
  while (front != NULL) { //traverse the queue
    if (isdigit(front->data)) { //is digit, just push to stack
      tree* temp = new tree(front);
      cout << temp->data << endl;
      pushTree(treestack, new tree(front));
    }
    else { //is operator, pop twice and assign right/left children
      tree* temp = new tree(front);
      temp->right = treestack;
      popTree(treestack);
      temp->left = treestack;
      popTree(treestack);
      pushTree(treestack, temp); //push
    }
    dequeue(front);
  }
  return treestack; //root 
}

//prints prefix notation
void prefix(tree* root) {
  if (root != NULL) {
    cout << root->data->data << " ";
    prefix(root->left);
    prefix(root->right);
  }
}

//prints infix notation
void infix(tree* root) {
  if (root != NULL) {
    infix(root->left);
    cout << root->data->data << " ";
    infix(root->right);
  }
}

//prints postfix notation
void postfix(tree* root) {
  if (root != NULL) {
    postfix(root->left);
    postfix(root->right);
    cout << root->data->data << " ";
  }
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
  if (top != NULL) {
    token* temp = top;
    top = top->next;
  }
}

//inserts tree node to top of stack
void pushTree(tree* &top, tree* data) {
  data->next = top;
  top = data;
}

//removes tree node from top of stack
void popTree(tree* &top) {
  if (top != NULL) {
    tree* temp = top;
    top = top->next;
  }
}

//retrieves token top of stack
char peek(token* top) {
  return top->data;
}

//prints linked list (stack or queue)
void print(token* head) {
  if (head != NULL) {
    cout << head->data << " ";
    print(head->next);
  }
}

//returns precedence of operator 
int precedence(char op/*erator*/) {
  if (op == '^') {
    return 4;
  }
  else if (op == '*') {
    return 3;
  }
  else if (op == '/') {
    return 3;
  }
  else if (op == '+') {
    return 2;
  }
  else if (op == '-') {
    return 2;
  }
  return 0;
}
