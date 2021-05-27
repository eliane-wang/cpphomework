#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void print(int* heap, int maxSize);
void heapify(int* heap, int maxSize, int i);
void heapSort(int* heap, int maxSize);

int main() {
  int maxSize = 101;
  int* heap = new int[maxSize];
  int indexCount = 1;
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
    heapSort(heap,maxSize);
    print(heap,maxSize);
    cout << endl;
  }
}


void print(int* heap, int maxSize) {
  cout << endl << "Heap represented as an array:" << endl << endl;
  for (int i = 0; i < maxSize; i++) {
    if (heap[i] != 0) { //within range
      cout << heap[i] << " ";
    }
  }
}

void heapify(int* heap, int maxSize, int i /*root*/) { //https://www.geeksforgeeks.org/heap-sort/
  int largest = i;
  int l = 2*i+1;
  int r = 2*i+2;
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
  for (int i = maxSize-1; i>0; i--) {
    heapify(heap,i,0);
  }
}
