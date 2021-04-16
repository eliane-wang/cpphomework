#ifndef NODE_H
#define NODE_H
#include "Student.h"

class Node {//Node Class
    public:
        Node(Student* newStudent);//constructor
        ~Node();//deconstructor
        void setStudent(Student* newStudent);//set student to Node
        Student* getStudent();//get Student
        void setNext(Node* newNode);//set next Node
        Node* getNext();//get Node
    private:
        Student* student;
        Node* next;
};
#endif
