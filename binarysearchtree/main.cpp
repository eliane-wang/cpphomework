/* Program creates a binary search tree. Users can ADD, PRINT, SEARCH or REMOVE.
   
   Date: 08.17.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//node struct with two children and a data value 
struct Node{ 
  int val = 0; 
  Node* left = NULL; 
  Node* right = NULL;
};

void add(Node* &node, int data);
void print(Node* node, int level);
void search(Node* root, int data);
struct Node* del(Node* &root, int data);

int main() {
  char command[8]; //commands
  bool running = true; 
  Node* root = NULL; //root of bst
  
  while (running == true) { //program runs until user quits
    cout << "Commands: PRINT, ADD, REMOVE, SEARCH, QUIT" << endl;
    cin >> command;
    if (strcmp(command, "PRINT") == 0) { //prints out tree
      print(root, 0);
    }
    else if (strcmp(command, "ADD") == 0) { //adds values to tree
      cout << "Select an input method: CONSOLE or FILE" << endl;
      cin >> command;
      if (strcmp(command, "CONSOLE") == 0) { //adding via console
	cout << "How many numbers are you adding?" << endl;
	int temp;
	cin >> temp;
	int counter = 0;
	cout << "Input your numbers: " << endl;
	while (counter != temp) {
	  int data;
	  cin >> data;
	  cin.get();
	  add(root, data);
	  counter++;
	}
      }
      else if (strcmp(command, "FILE") == 0) { //adding via file
	cout << "Enter a filename (ex. 'numbers.txt'): " << endl;
	char filename[20];
	cin >> filename;
	int data;
	ifstream myfile (filename);
	if (myfile.is_open()) {
	  while (!myfile.eof()) {
	    myfile >> data;
	    add(root, data);
	  }
	  myfile.close();
	}
	else { //invalid file name
	  cout << "Unable to open or locate file" << endl;
	}
      }
      else { 
	cout << "Invalid input method!" << endl;
      }
    }
    else if (strcmp(command, "REMOVE") == 0) { //deletes a value from the tree
      cout << "Enter a value to remove: " << endl;
      int data;
      cin >> data;
      del(root, data);
    }
    
    else if (strcmp(command, "SEARCH") == 0) { //searches the tree for a value
      cout << "Enter a value to search for: " << endl;
      int data;
      cin >> data;
      search(root, data);
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
void add(Node* &node, int data) {
  if (node == NULL) { //if tree empty, set root 
    node = new Node();
    node->val = data;
    return;
  }
  if (node->val > data) { //data belongs on left subtree
    if (node->left == NULL) { //insert data to empty node
      Node* temp = new Node();
      temp->val = data;
      node->left = temp;
    }
    else { //add to left subtree
      Node* temp = node->left;
      add(temp, data);
    }
  }
  if (node->val <= data) { //data belongs on right subtree
    if (node->right == NULL) { //insert data to empty node
      Node* temp = new Node();
      temp->val = data;
      node->right = temp;
    }
    else { //add to right subtree
      Node* temp = node->right;
      add(temp, data);
    }
  }
  
}

//searches bst to find specific values
void search(Node* root, int data) { //reference: https://www.youtube.com/watch?v=COZK7NATh4k
  if (root == NULL) { //value does not exist
    cout << "The tree does not contain " << data << endl;
    return;
  }
  else if (root->val == data) { //found
    cout << "The tree contains " << data << endl;
  }
  else if (data <= root->val) { //search left subtree
    return search(root->left, data);
  }
  else { //search right subtree
    return search(root->right, data);
  }
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
  cout << node->val << endl;
  print (node->left, level); //left subtree
}

//deletes a specific number from the tree
struct Node* del(Node* &root, int data) { //reference: https://www.youtube.com/watch?v=gcULXE7ViZw
  if (root == NULL) { //empty
    return root;
  }
  else if (data < root->val) { //check the left subtree
    root->left = del(root->left, data);
  }
  else if (data > root->val) { //check the right subtree
    root->right = del(root->right, data);
  }
  else { //found 
    if (root->left == NULL && root->right == NULL) { //node has no children
      delete root;
      root = NULL;
    }
     else if (root->left == NULL) { //node has right child
      struct Node *temp = root;
      root = root->right;
      delete temp;
    }
    else if (root->right == NULL) { //node has left child
      struct Node *temp = root;
      root = root->left;
      delete temp;
    }
    else { //node has right and left child
      struct Node* temp = root->right;
      while (temp->left != NULL) { //find minimum node
	temp = temp->left;
      }
      root->val = temp->val;
      root->right = del(root->right, temp->val);
    }
  }
  return root;
}

