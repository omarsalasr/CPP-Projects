#include <cstdio>
#include <cstring>
#include <cstdlib>

//my node class
class MyNode
{
  private:
    int elem;//element value 
    MyNode* next;//pointer to the next node
  
  public:
    MyNode (int v1);
    MyNode (int v1, MyNode* n);
    void setElem (int e);
    int getElem();
    void setNext (MyNode* n);
    MyNode* getNext();
};

//my node class
class MyFileNode
{
  private:
    char* elem;//element value 
    MyFileNode* next;//pointer to the next node
  
  public:
    MyFileNode (char* v1, MyFileNode* n);
    char* getElem ();
    void setNext (MyFileNode* n);
    MyFileNode* getNext();
};

//my list class
class MyList
{
 private:
  MyNode* head;//head pointer
  int size;//number of elements in the list
  
 public:
  MyList();
  bool contains(int n);
  void insertFront(int v1);
  void remove(int v1);
  int getSize();
  int getNthValue(int n);
  void printList();
};

//file list
class MyFileList
{
 private:
  MyFileNode* head;//head pointer
  int size;//number of elements in the list
  
 public:
  MyFileList();
  bool contains(char* n);
  void insertFront(char* v1);
  void remove(char* v1);
  int getSize();
};

//airport class
class Airport{
  private:
    bool visited;//boolean for visited 
    MyList* adjList;//pointer to the front of a linked list

  public:
    Airport();
    void changeVisited(bool v);
    void resetVisit();
    bool wasVisited();
    MyList* getList();
};