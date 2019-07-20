#include "Proj6.h"

  MyFileList::MyFileList(){//constructor
    head = NULL;
    size = 0;
  }
  //method that checks if a value is contained in the list already
  bool MyFileList::contains(char* n){
    if(getSize() == 0)//list is empty
      return false;
    MyFileNode* travel = head;
    while(travel != NULL){//traverse through the list and find the value
      if(strcmp(travel->getElem(),n) == 0)
        return true;
      travel = travel->getNext();
    }
    return false;
  }

  //insert a node at the front
  void MyFileList::insertFront(char* v1){
    if(contains(v1))//check if it's already in the list
      return;
    MyFileNode* temp = new MyFileNode(v1,head);
    head = temp;
    size++;
  }

  //remove the node with a given element
  void MyFileList::remove(char* v1){
    MyFileNode* del = head;
    if(strcmp(head->getElem(),v1) == 0){//check the front
      head->setNext(head->getNext());
      delete del;
      size--;
      return;
    }
    MyFileNode* travel = head;
    while(travel->getNext() != NULL){//traverse through the list
      if(strcmp(travel->getNext()->getElem(),v1) == 0){//found the item
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
  int MyFileList::getSize(){
    return size;
  }