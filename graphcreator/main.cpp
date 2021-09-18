/* Create a directed graph represented by an adjacency table. Users have the ADD (vertices/edges), REMOVE (vertices/edges), PATH (find the shortest path using Dijkstra's algorithm), and PRINT commands.

  References: https://www.educative.io/edpresso/how-to-implement-dijkstras-algorithm-in-cpp
              https://www.softwaretestinghelp.com/graph-implementation-cpp/

  Date: 09.17.2021
  Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

//vertex struct with label 
struct vertex{
  char label;
  vertex(char newlabel) {
    label = newlabel;
  }
};

void addVertex(vertex** list);
void addEdge(vertex** list, int adjacencyMatrix[20][20]);
void removeVertex(vertex** vertexList, int adjacencyMatrix[20][20]);
void removeEdge(vertex** list, int adjacencyMatrix[20][20]);
void findShortestPath(vertex** vertexList, int adjacencyMatrix[20][20]);
int minimumDist(int distance[20], bool visited[20]);

int main() {
  char command[8]; 
  bool running = true;
  vertex* vertexList[20]; //stores list of vertices
  int adjacencyMatrix[20][20]; //stores the adjacency table
    
  for (int i = 0; i < 20; i++) { //initialize
    vertexList[i] = NULL;
  }
  
  for (int x = 0; x < 20; x++) { //initialize
    for (int y = 0; y < 20; y++) {
      adjacencyMatrix[x][y] = 0;
    }
  }
  
  while (running == true) { //program runs until user quits
    cout << "Commands: ADD, REMOVE, PATH, PRINT, QUIT" << endl;
    cin >> command;
    if (strcmp(command, "ADD") == 0) { //adds (vertices or edges)
      cout << "VERTEX or EDGE " << endl;
      cin >> command;
      if (strcmp(command, "VERTEX") == 0) { //adds vertices
	addVertex(vertexList);
      }
      else if (strcmp(command, "EDGE") == 0) { //adds edges
	addEdge(vertexList, adjacencyMatrix);
      }
      else { //unrecognized command
	cout << "Invalid ADD method." << endl;
      }
    }
    else if (strcmp(command, "REMOVE") == 0) { //removes (vertices or edges)
      cout << "VERTEX or EDGE " << endl;
      cin >> command;
      if (strcmp(command, "VERTEX") == 0) { //removes vertices
	removeVertex(vertexList, adjacencyMatrix);
      }
      else if (strcmp(command, "EDGE") == 0) { //removes edges
	removeEdge(vertexList, adjacencyMatrix);
      }
      else { //unrecognized command
	cout << "Invalid REMOVE method. " << endl;
      }
    }
    else if (strcmp(command, "PATH") == 0) { //returns shortest path
      findShortestPath(vertexList, adjacencyMatrix);
    }
    else if (strcmp(command, "PRINT") == 0) { //prints adjacency matrix
      cout << "Adjacency Matrix: " << endl;
      for (int i = 0; i < 20; i++) {
	if (vertexList[i] != NULL) {
	  cout << " " << vertexList[i]->label;
	}
	else {
	  cout << "  ";
	}
      }
      cout << endl;
      for (int i = 0; i < 20; i++) {
	if (vertexList[i] != NULL) {
	  cout << vertexList[i]->label;
	}
	else {
	  cout << " ";
	}
	for (int j = 0; j < 20; j++) {
	  cout << adjacencyMatrix[i][j] << " ";
	}
	cout << endl;
      }
    }
    else if (strcmp(command, "QUIT") == 0) { //quits the program
      running = false;
    }
    else { //unrecognized input
      cout << "Invalid command." << endl;
    }
  }
}

//enter a label for a vertex and add it to the graph
void addVertex(vertex** list) {
  cout << "Enter a label for a vertex: " << endl;
  char label;
  cin >> label;
  for (int i = 0; i < 20; i++) { //finds an empty spot
    if (list[i] == NULL) { //adds new vertex
      vertex* v = new vertex(label);
      list[i] = v;
      return;
    }
  }
  cout << "The table is full." << endl;
  return;
}

//add a weighted edge between an initial and terminating vertex
void addEdge(vertex** list, int adjacencyMatrix[20][20]) {
  char initial;
  cout << "Enter the label of the initial vertex: " << endl;
  cin >> initial;
  char terminal;
  cout << "Enter the label of the terminating vertex: " << endl;
  cin >> terminal;
  int weight;
  cout << "Enter a weight for the edge: " << endl;
  cin >> weight;
  int initialIndex, terminalIndex;
  
  for (int i = 0; i < 20; i++) { //iterates through the list
    if (list[i] != NULL) {
      if (list[i]->label == initial) { //located
	initialIndex = i;
      }
      else if (list[i]->label == terminal) { //located
	terminalIndex = i;
      }
    }
  }
  adjacencyMatrix[initialIndex][terminalIndex] = weight; //updates adjacency matrix
}

//removes a vertex from the graph and its associated edges
void removeVertex(vertex** vertexList, int adjacencyMatrix[20][20]) {
 cout << "Enter a label for a vertex: " << endl;
  char label;
  cin >> label;
  int deleteIndex;
  for (int i = 0; i < 20; i++) { //iterates through the list
    if (vertexList[i] != NULL) {
      if (vertexList[i]->label == label) { //located
	cout << "Found and deleted." << endl;
	deleteIndex = i;
      }
    }
  }
  for (int i = 0; i < 20; i++) { //removes associated edges
    adjacencyMatrix[i][deleteIndex] = 0;
    adjacencyMatrix[deleteIndex][i] = 0;
  
  }
  delete vertexList[deleteIndex];
  vertexList[deleteIndex] = NULL;
}

//removes an edge between two vertices
void removeEdge(vertex** vertexList, int adjacencyMatrix[20][20]) {
 char initial;
  cout << "Enter the label of the initial vertex: " << endl;
  cin >> initial;
  char terminal;
  cout << "Enter the label of the terminating vertex: " << endl;
  cin >> terminal;
  int initialIndex, terminalIndex;
  
  for (int i = 0; i < 20; i++) { //iterates through the list
    if (vertexList[i] != NULL) {
      if (vertexList[i]->label == initial) { //located
        initialIndex = i;
      }
      else if (vertexList[i]->label == terminal) { //located
        terminalIndex = i;
      }
    }
  }
  adjacencyMatrix[initialIndex][terminalIndex] = 0; //updates adjacency matrix
}

//enter two vertex labels and use Dijkstra's algorithm to find the shortest path
void findShortestPath(vertex** vertexList, int adjacencyMatrix[20][20]) {
 char initial;
  cout << "Enter the label of the initial vertex: " << endl;
  cin >> initial;
  char terminal;
  cout << "Enter the label of the terminating vertex: " << endl;
  cin >> terminal;
  int initialIndex, terminalIndex;

  for (int i = 0; i < 20; i++) { //iterates through the list
    if (vertexList[i] != NULL) {
      if (vertexList[i]->label == initial) { //located
        initialIndex = i;
      }
      else if (vertexList[i]->label == terminal) { //located
        terminalIndex = i;
      }
    }
  }
  int distance[20]; //min distance for each vertex
  bool visited[20]; //if vertex has been visited or not
  for (int i = 0; i < 20; i++) { //mark all existing vertices unvisited with infinite distance
    distance[i] = 2147483647; //int max
    visited[i] = false;
    if (vertexList[i] == NULL) { //nonexistent vertices
      visited[i] = true;
    }
  }
  distance[initialIndex] = 0; //initial vertex has distance 0
  for (int i = 0; i < 20; i++) { 
    int m = minimumDist(distance, visited);
    visited[m] = true;
    for (int i = 0; i < 20; i++) {
      if (!visited[i] && adjacencyMatrix[m][i] && distance[m] != 2147483647 && distance[m] + adjacencyMatrix[m][i] < distance[i]) { //updates distance calculation
	  distance[i] = distance[m]+adjacencyMatrix[m][i];
	}
      }
    }
  }
if (distance[terminalIndex] != 0 && distance[terminalIndex] != 2147483647) { //output the shortest path
  cout << "Shortest Path: " << distance[terminalIndex] << endl;
 }
 else { //not found
   cout << "Path doesn't exist." << endl;
 }
}

//returns the minimum distance traveled
int minimumDist(int distance[20], bool visited[20]) {
  int min = 2147483647; //int max
  int index;
  for (int i = 0; i < 20; i++) { //for each vertex
    if (visited[i] == false && distance[i]<=min) { //update min distance
      min = distance[i];
      index = i;
    }
  }
  return index;
}
