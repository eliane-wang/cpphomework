/* Creates a max heap from entered numbers or a file (containing a space-separated list of numbers). 
   
   Date: 07.16.2021
   Author: Eliane Wang */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void print(int* heap, int i, int level, int indexCount);
void heapify(int* heap, int maxSize, int i);
void heapSort(int* heap, int maxSize);
void remove(int* heap, int indexCount);
void deleteRoot(int* heap, int& indexCount);

int main() {
  int maxSize = 100; //heap stores up to 100 numbers
  int* heap = new int[maxSize];
  for (int i = 0; i < maxSize; i++) { //heap values empty
    heap[i] = 0;
  }
  int indexCount = 0; //size of heap
  char command[7]; //commands
  
  cout << "Select an input method: 'MANUAL' or 'FILE'?" << endl;
  cin >> command;
  if (strcmp(command, "MANUAL") == 0) {//reads in numbers from console
    cout << "How many numbers are you adding?" << endl;
    int temp;
    cin >> temp;
    int counter = 0;
    cout << "Input your numbers: " << endl;
    while (counter != temp) {
      cin >> heap[indexCount];
      counter++;
      indexCount++;
    }    
  }
  if (strcmp(command, "FILE") == 0) { //reads in from file
    cout << "enter a filename (ex. 'heap.txt'): " << endl;
    char filename[10];
    cin >> filename;
    int heapdata;
    ifstream myfile (filename);
    if (myfile.is_open()) {
      while (!myfile.eof()) { //not end of line
	myfile >> heap[indexCount];
	indexCount++;
      }
      myfile.close();
    }
    else { //invalid file name
      cout << "unable to open file " << endl;
    }
  }
  cout << endl;
  heapSort(heap,indexCount); //sorts array to heap
  cout << endl;
  cout << "Displaying the heap: " << endl;  
  print(heap,0,0,indexCount); //heap represented as tre
  cout << endl << endl;
  remove(heap,indexCount); //each element removed
}

//prints the heap in a tree  
void print(int* heap, int i, int level, int indexCount) {
  if (heap[i] != 0 && i < indexCount) { //element exists
    level++;
    print(heap,i*2+2,level, indexCount); //right child
    cout << endl;
    for (int i = 1; i < level; i++) {
      cout << "\t";
    }
    cout << heap[i];
    print(heap,i*2+1,level, indexCount); //left child
  }
}

//rearranges nodes to maintain the max heap properties 
void heapify(int* heap, int maxSize, int i) { //sourced from: geeksforgeeks.org/heap-sort/
  int largest = i;
  int l = 2*i+1;//left
  int r = 2*i+2;//right
  if (l<maxSize && heap[l] > heap[largest]) { //if left child is largest
    largest = l;
  }
  if (r < maxSize && heap[r] > heap[largest]) { //if right child is largest
    largest = r;
  }
  if (largest != i) { //rearranges if largest is not root
    swap(heap[i], heap[largest]);
    heapify(heap,maxSize,largest);
  }
}

//builds the max heap by rearranging the array
void heapSort(int* heap, int maxSize) {
  for (int i = maxSize/2-1; i >= 0; i--) {
    heapify(heap,maxSize,i);
  }
}

//deletes the root from the heap by replacing current root with last element
void deleteRoot(int* heap, int& indexCount) {
  int last = heap[indexCount-1];
  cout << heap[0] << " "; //outputs
  heap[0] = last; 
  indexCount -= 1;
  heapify(heap,indexCount,0);
}

//removes each element from the heap
void remove(int* heap, int indexCount) {
  cout << endl << "Removing from the heap: " << endl;
  int n = indexCount; 
  for (int i = 0; i < n; i++) {
    deleteRoot(heap,indexCount); //deletes current root and updates heap
  }
}
