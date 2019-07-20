#include "Proj6.h"

  MyList::MyList(){//constructor
    head = NULL;
    size = 0;
  }
  
  //method that checks if a value is contained in the list already
  bool MyList::contains(int n){
    if(size == 0)
      return false;
    MyNode* travel = head;
    while(travel != NULL){//traverse through the list and find the value
      if(travel->getElem() == n){
        return true;
      }
      travel = travel->getNext();
    }
    return false;
  }
  //insert a node at the front
  void MyList::insertFront(int v1){
    if(contains(v1))//check if it's already in the list
      return;
    MyNode* temp = new MyNode(v1,head);
    head = temp;
    size++;
  }

  //remove the node with a given element
  void MyList::remove(int v1){
    MyNode* del = head;
    if(head->getElem() == v1){//check the front
      size--;
      head = head->getNext();
      delete del;
      return;
    }
    MyNode* travel = head;
    while(travel->getNext() != NULL){//traverse through the list
      if(travel->getNext()->getElem() == v1){//found the item
        del = travel->getNext();
        travel->setNext(travel->getNext()->getNext());//set pointers
        delete del;
        size--;
        return;
      }
      travel = travel->getNext();
    }
    //the node is not in the list
  }
  //returns the number of values in the list
  int MyList::getSize(){
    return size;
  }
  //returns the value at the nth position 1...n
  int MyList::getNthValue(int n){
    if(n > size || n < 0)//check if n is a valid input
      return -999;
    else if(n == 0)//wanted value is at the front
      return head->getElem();
    MyNode* travel = head->getNext();
    int counter = 1;//counter to keep track of the current position
    while(travel != NULL){//traverse until the position is found
      if(counter == n)
        return travel->getElem();
      counter++;
      travel = travel->getNext();
    }
  }

   void MyList::printList(){//prints the list
      MyNode* temp = head;
      while(temp != NULL){
        printf("%d, ", temp->getElem());
        temp = temp->getNext();
      }
    }