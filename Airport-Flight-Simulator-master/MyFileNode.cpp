#include "Proj6.h"

    //constructor
    MyFileNode::MyFileNode (char* v1, MyFileNode* n){
      elem = v1;
      next = n;
    }

    //returns the element
    char* MyFileNode::getElem (){
      return elem;
    }

    //modifies the next pointer
    void MyFileNode::setNext (MyFileNode* n){
      next = n;
    }

    //returns the next pointer
    MyFileNode* MyFileNode::getNext(){
      return next;
    }