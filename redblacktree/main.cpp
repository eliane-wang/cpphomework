/* Parts 1 and 2 of the Red Black Tree Assignment. Users can ADD, READ, PRINT, SEARCH, DELETE or QUIT.
 
  References: https://www.youtube.com/watch?v=A3JZinzkMpk
              https://www.programiz.com/dsa/red-black-tree
              https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/

  Date: 06.15.2022
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
Node* search(Node* node, int data);
Node* deleteNode(Node* &root, Node* n);
void doubleBlack(Node* &root, Node* &n);

  
int main() {
  char command[8]; //commands
  bool running = true;
  Node* root = NULL; //root of rbt

  while (running == true) { //program runs until user quits
    cout << "Commands: ADD, READ, PRINT, SEARCH, DELETE, QUIT" << endl;
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
    else if (strcmp(command, "SEARCH") == 0) { //searches the tree for a node
      cout << "Enter a value to search for: " << endl;
      int data;
      cin >> data;
      Node* n = new Node;
      n = search(root, data);
      }
    else if (strcmp(command, "DELETE") == 0) { //deletes a node from tree
      cout << "Enter a value to delete: " << endl;
      int data;
      cin >> data;
      Node* n = new Node;
      cout << "Searching... " << endl;
      n = search(root, data);
      if (n != NULL) { //node exists
        cout << "Deleting... " << endl;
        cout << "The tree no longer contains " << n->val << endl;
        root = deleteNode(root, n);  
      }
    }
    else if (strcmp(command, "QUIT") == 0) { //quits the program; terminates running loop
      cout << "Quitting...";
      running = false;
    }
    else { //reprompts user to enter correct command
      cout << "Invalid command! Please try again." << endl;
    }
    cout << endl;
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

//searches tree and returns node
Node* search(Node* node, int data) { 
  if (node == NULL) { //value does not exist
    cout << "The tree does not contain " << data << endl;
    return NULL;
  }
  else if (node->val == data) { //found
    cout << "The tree contains " << data << endl;
    return node;
  }
  else if (data <= node->val) { //search left subtree
    return search(node->left, data);
  }
  else { //search right subtree
    return search(node->right, data);
  }
}

Node* deleteNode(Node* &root, Node* n){ //deletes a node from tree
  bool dB = false; //doubleblack
  if (root == NULL) { //tree is empty
    return root;
  }
  else if (root->left == NULL && root->right == NULL) { //tree contains one node
    return NULL;
  }
  else {
    if (n->left == NULL && n->right == NULL) { //has no children
      if (n->color == 'B') { //black
        n->val = 0;
        doubleBlack(root, n); //correct double black
      }
      if (n->parent->left == n) { //is left child
        n->parent->left = NULL; //remove
      }
      else { //is right child
        n->parent->right = NULL; //remove
      }
      return root;
    }
    else if (n->left == NULL) { //has one child (right)
    Node* temp = n->right;
    if (n->color == 'R' || n->right->color == 'R') { //recolor
      temp->color = 'B';
    }
    else if (n->right == NULL || n->right->color == 'B') { //double black
      dB = true;
    }
    if (n->parent) { //has parent
      if (n->parent->right == n) { //is right child
        n->parent->right = temp;
      }
      else { //is left child
        n->parent->left = temp;
      }
      temp->parent = n->parent;
    }
    else {
      root = temp;
    }
    if (dB) { //correct double black
      doubleBlack(root, temp);
    }
  }
  else if (n->right == NULL) { //has one child (left)
    Node* temp = n->left;
    if (n->color == 'R' || n->left->color == 'R') { //recolor
      temp->color = 'B';
    }
    else if (n->left == NULL || n->left->color == 'B') { //double black
      dB = true;
    }
    if (n->parent) {
      if (n->parent->right == n) {
        n->parent->right = temp;
      }
      else {
        n->parent->left = temp;
      }
      temp->parent = root->parent;
    }
    else {
      root = temp;
    }
    if (dB) {
      doubleBlack(root, temp);
    }
  }
  else { //two children
    Node * s = n->right;
    while (s->left != NULL) { //successor
      s = s->left;
    }
    n->val = s->val;
    deleteNode(root, s);
    return root;
    }
  }
  return root;
}

void doubleBlack(Node* &root, Node* &n) {
  if (root == n) {
    return;
  }
  Node *p = n->parent; //parent
  Node *s = n; //sibling
  if (p->right == n) { //sibling is left child
    s = p->left;
  }
  else { //sibling is right child
    s = p->right;
  }
  if (s == NULL) {
    doubleBlack(root, p);
  }
  else {
    if (s->color == 'R') { //sibling is red
      p->color = 'R';
      s->color = 'B';
      if (p->left == s) {
        rotateRight(root, p);
      }
      else {
        rotateLeft(root, p);
      }
      doubleBlack(root, n);
    }
    else { //sibling is black
    if ((s->left && s->left->color == 'R') || (s->right && s->right->color == 'R')) { //sibling has red child
      if (s->left && s->left->color == 'R') { //left child is red
        if (p->left == s) {
          s->left->color = s->color;
          s->color = p->color;
          rotateRight(root, p);
        }
        else {
          s->left->color = p->color;
          rotateRight(root, s);
          rotateLeft(root, p);
        }
      }
      else { //right child is red
        if (p->left == s) {
          s->right->color = p->color;
          rotateLeft(root, s);
          rotateRight(root, p);
        }
        else {
          s->right->color = s->color;
          s->color = p->color;
          rotateLeft(root, p);
        }
      }
      p->color = 'B';
    }
    else { //both children are black
      s->color = 'R';
      if (p->color == 'B') {
        doubleBlack(root, p);
      }
      else {
        p->color = 'B';
        }
      }
    }
  }
}
