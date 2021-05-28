#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void printArr(int* heap, int maxSize);
void print(int* heap, int i, int level);
void heapify(int* heap, int maxSize, int i);
void heapSort(int* heap, int maxSize);

int main() {
  int maxSize = 101;
  int* heap = new int[maxSize];
  for (int i = 0; i < maxSize; i++) {
    heap[i] = 0;
  }
  int indexCount = 0;
  char command[7];
  bool running = true;

  while (running == true) {
    if (indexCount == maxSize) {
      cout << "Heap full!" << endl;
    }
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
      running = true;
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
      else {
	cout << "unable to open file " << endl;
      }
    }
    cout << endl;
    heapSort(heap,indexCount);
    printArr(heap,maxSize);
    cout << endl;
    
    print(heap,0,0);
    
    cout << endl;
  }
}


void printArr(int* heap, int maxSize) {
  cout << endl << "Array: " << endl << endl;
  for (int i = 0; i < maxSize; i++) {
    //if (heap[i] != 0) { //within range
      cout << heap[i] << " ";
      //}
  }
}


//prints tree 
void print(int* heap, int i, int level) {
  if (heap[i] != 0) {
  level++;
  print(heap,i*2+2,level); //right
  cout << endl;
  for (int i = 1; i < level; i++) {
    cout << "\t";
  }
  cout << heap[i];
  print(heap,i*2+1,level); //left
  }
}
void heapify(int* heap, int maxSize, int i /*root*/) { //https://www.geeksforgeeks.org/heap-sort/
  int largest = i;
  int l = 2*i+1;//left
  int r = 2*i+2;//right
  if (l<maxSize && heap[l] > heap[largest]) {
    largest = l;
  }
  if (r < maxSize && heap[r] > heap[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(heap[i], heap[largest]);
    heapify(heap,maxSize,largest);
  }
}

void heapSort(int* heap, int maxSize) {
  for (int i = maxSize/2-1; i >= 0; i--) {
    heapify(heap,maxSize,i);
  }
}
