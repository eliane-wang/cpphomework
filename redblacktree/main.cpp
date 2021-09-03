/* Part 1 of the Red Black Tree Assignment. Users can ADD, READ, PRINT or QUIT.
 
  References: https://www.youtube.com/watch?v=A3JZinzkMpk
              https://www.programiz.com/dsa/red-black-tree

  Date: 09.03.2021
  Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//node struct with a left/right child, parent, data value, and color 
struct Node{
  Node* left = NULL;
  Node* right = NULL;
  Node* parent = NULL;
  int val = 0;
  char color = 'R';
};

Node* add(Node* &node, int data);
void rotateLeft(Node* &root, Node* &node);
void rotateRight(Node* &root, Node* &node);
void fix(Node* &root, Node* &node);
void print(Node* node, int level);

int main() {
  char command[8]; //commands
  bool running = true;
  Node* root = NULL; //root of rbt

  while (running == true) { //program runs until user quits
    cout << "Commands: ADD, READ, PRINT, QUIT" << endl;
    cin >> command;
    if (strcmp(command, "ADD") == 0) { //adds values to tree
      cout << "Enter your number: " << endl;
      int data;
      cin >> data;
      cin.get();
      Node* n = new Node;
      n = add(root, data);
      fix(root, n);
    }
    else if (strcmp(command, "READ") == 0) { //adding via file name
      cout << "Enter a filename (ex. 'numbers.txt'): " << endl;
      char filename[20];
      cin >> filename;
      int data;
      ifstream myfile(filename);
      if (myfile.is_open()) { //found 
	while (!myfile.eof()) {
	  myfile >> data;
	  Node* n = new Node;
	  n = add(root, data);
	  fix(root, n);
	}
	myfile.close();
      }
      else { //invalid request
	cout << "Unable to open or locate file" << endl;
      }
    }
    else if (strcmp(command, "PRINT") == 0) { //prints out tree
      print(root, 0);
    }
    else if (strcmp(command, "QUIT") == 0) { //quits the program; terminates running loop
      cout << "Quitting...";
      running = false;
    }
    else { //reprompts user to enter correct command
      cout << "Invalid command! Please try again." << endl;
    }
  }
}

//adds nodes to the tree 
Node* add(Node* &node, int data) {
  if (node == NULL) { //if tree empty, set root 
    node = new Node();
    node->val = data;
    return node;
  }
  if (node->val > data) { //data belongs on left subtree
    if (node->left == NULL) { //insert data to empty node
      Node* temp = new Node();
      temp->val = data;
      node->left = temp;
      temp->parent = node;
      return temp;
    }
    else { //add to left subtree
      Node* temp = node->left;
      return add(temp, data);
    }
  }
  if (node->val <= data) { //data belongs on right subtree
    if (node->right == NULL) { //insert data to empty node
      Node* temp = new Node();
      temp->val = data;
      node->right = temp;
      temp->parent = node;
      return temp;
    }
    else { //add to right subtree
      Node* temp = node->right;
      return add(temp, data);
    }
  }
  return NULL;
}

//perform a left rotation on the tree to given node
void rotateLeft(Node* &root, Node* &node) {
  Node* r = node->right;
  node->right = r->left;
  if (node->right != NULL) { //change node parent
    node->right->parent = node;
  }
  r->parent = node->parent;
  if (node->parent == NULL) { //node is root
    root = r;
  }
  else if (node == node->parent->left) { //is left child
    node->parent->left = r;
  }
  else { //is right child
    node->parent->right = r;
  } //set r to left child of node
  r->left = node;
  node->parent = r;
}

//perform a right rotation on the tree to given node 
void rotateRight(Node* &root, Node* &node) {
  Node* l = node->left;
  node->left = l->right;
  if (node->left != NULL) { //change node parent
    node->left->parent = node;
  }
  l->parent = node->parent;
  if (node->parent == NULL) { //node is root
    root = l;
  }
  else if (node == node->parent->left) { //is left child
    node->parent->left = l;
  }
  else { //is right child 
    node->parent->right = l;
  } //set l the right child of node
  l->right = node;
  node->parent = l;
}

//rearranges tree to fufill the rbt properties 
void fix(Node *&root, Node *&node) {
  Node *p = NULL; //parent
  Node *g = NULL; //grandparent
  Node* u = NULL; //uncle
  while ((node != root) && (node->color == 'R') && (node->parent->color == 'R')){ //both the node and the parent are red 
    p = node->parent;
    g = node->parent->parent;
    if (p == g->left) { //parent is left child
      u = g->right;
      if (u != NULL && u->color == 'R') { //red uncle (recolor)
	g->color = 'R';
	p->color = 'B';
	u->color = 'B';
	node = g;
      }
      else {
	  if (node == p->right) { //node is right child (rotate left)
	      rotateLeft(root, p);
	      node = p;
	      p = node->parent;
	  } //node is left child (rotate right)
	  rotateRight(root, g);
	  p->color = 'B';
	  g->color = 'R';
	  node = p;
	}
    }
    else { //parent is right child
	u = g->left;
	if ((u != NULL) && (u->color == 'R')) { //red uncle (recolor)
	  g->color = 'R';
	  p->color = 'B';
	  u->color = 'B';
	  node = g;
	}
	else {
	  if (node == p->left) { //node is left child (rotate right)
	    rotateRight(root, p);
	    node = p;
	    p = node->parent;
	  } //node is right child (rotate left)
	  rotateLeft(root, g);
	  p->color = 'B';
	  g->color = 'R';
	  node= p;
	}
    }
  }
  root->color = 'B'; //recolor root of tree 
}

//prints the tree showing the parent-child relationships 
void print(Node* node, int level) {
  if (node == NULL) { //empty
    return;
  }
  level++;
  print(node->right, level); //right subtree
  cout << endl;
  for (int i = 1; i < level; i++) {
    cout << "\t";
  }
  cout << node->val << node->color << endl;
  print (node->left, level); //left subtree
}
  
