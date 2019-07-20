#include "Proj6.h"

    //constructor
    MyNode::MyNode (int v1){
      elem = v1;
      next = NULL;
    }
    //overloaded constructor
    MyNode::MyNode (int v1, MyNode* n){
      elem = v1;
      next = n;
    }
    //modify the element
    void MyNode::setElem (int e){
      elem = e;
    }
    //returns the element
    int MyNode::getElem(){
      return elem;
    }
    //modifies the next pointer
    void MyNode::setNext (MyNode* n){
      next = n;
    }
    //returns the next pointer
    MyNode* MyNode::getNext(){
      return next;
    }