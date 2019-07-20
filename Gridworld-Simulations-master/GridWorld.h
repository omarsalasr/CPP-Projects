
#include "GWInterface.h"
#include <vector>
#include <iostream>

using std::vector;


class GridWorld : public GWInterface {

  public:
    GridWorld(unsigned nrows, unsigned ncols){
      numCols = ncols;
      numRows = nrows;
      printf("%d %d\n", numCols, numRows);
      int i, j;
      grid = new District*[nrows];
	    for(i = 0; i < nrows; i++){
        grid[i] = new District[ncols];
      }
      pplSize = 10;
      popul = 0;
      people = new Person[pplSize];
      // for(j = 0; j < pplSize; j++){
      //   printf("%d %d %d %p\n", people[j].r, people[j].c, people[j].alive, people[j].node);
      // }

    }
    ~GridWorld(){
      // your destructor code here.
    }
    // O(1)
    //
    bool birth(int row, int col, int &id){
      if(isValidCoor(row, col)){
        if(graveyard.population != 0){
          printf("Not empty\n");
          id = graveyard.membersFront->data;
          Node *del = graveyard.membersFront;
          if(graveyard.population == 1){
            graveyard.membersFront = graveyard.membersBack = nullptr;
          }else{
            graveyard.membersFront = graveyard.membersFront->next;
            graveyard.membersFront->prev = nullptr;
          }
          graveyard.population -= 1;
          delete del;
          printf("foianwfoino\n");
        }else
          id = popul;
        if(popul >= pplSize)
          growArray();
        popul++;
        grid[row][col].population += 1;
        Node *temp = new Node();
        if(grid[row][col].population == 1){
          temp->prev = nullptr;
          grid[row][col].membersFront = temp;
        }else{
          temp->prev = grid[row][col].membersBack;
          grid[row][col].membersBack->next = temp;
        }
        temp->next = nullptr;
        temp->data = id;
        people[id].r = row;
        people[id].c = col;
        people[id].alive = true;
        people[id].node = temp;
        grid[row][col].membersBack = temp;
        // printf("%p %p %d\n", temp,grid[row][col].membersBack, grid[row][col].membersBack->data);
        return true;

      }
      // printf("%d %d %d %p\n", people[id].r, people[id].c, people[id].alive, people[id].node);
      return false;
    }
    // O(1)
    // Toggle alive boolean
    bool death(int personID){
      if(people[personID].alive){
        // printf("Tis' zero\n");
        Node *dead = people[personID].node;
        if(dead == grid[people[personID].r][people[personID].c].membersFront){
          grid[people[personID].r][people[personID].c].membersFront = grid[people[personID].r][people[personID].c].membersFront->next;
          grid[people[personID].r][people[personID].c].membersFront->prev = nullptr;
        }else if(dead == grid[people[personID].r][people[personID].c].membersBack){
          grid[people[personID].r][people[personID].c].membersBack = grid[people[personID].r][people[personID].c].membersBack->prev;
          grid[people[personID].r][people[personID].c].membersBack->next = nullptr;
        }else{
          Node *temp = dead->prev;
          temp->next = temp->next->next;
          temp = temp->next;
          temp->prev = temp->prev->prev;
        }
        dead->next = nullptr;
        if(graveyard.population == 0){
          dead->prev = nullptr;
          graveyard.membersFront = dead;
          graveyard.membersBack = dead;
        }else{
          dead->prev = graveyard.membersBack;
          graveyard.membersBack->next = dead;
          graveyard.membersBack = graveyard.membersBack->next;
        }
        people[personID].alive = false;
        graveyard.population += 1;
        grid[people[personID].r][people[personID].c].population -= 1;
        popul -= 1;
        return true;
      }
      return false;
    }
    // O(1)
    // People array with index of ID, pass in the ID and get the r and c
    bool whereis(int id, int &row, int &col)const{
      if(popul == 0)
        return false;
      else if(people[id].alive){
        row = people[id].r;
        col = people[id].c;
        return true;
      }
      return false;
    }
    // O(1)
    // Move from r, c to new r, c... make sure that they are alive
    // Change their r and c
    bool move(int id, int targetRow, int targetCol){
      
      return false;
    }

    std::vector<int> * members(int row, int col)const{
      std::vector<int> * disMembers = new std::vector<int>();
      if(isValidCoor(row, col))
        if(grid[row][col].population != 0){
          int i;
          Node *temp = grid[row][col].membersFront;
          while(temp != nullptr){
            disMembers->push_back(temp->data);
            temp = temp->next;
          }
        }
      return disMembers;
    }


    int population()const{
      return popul;
    }
    int population(int row, int col)const{
      if(isValidCoor(row, col)){
        return grid[row][col].population;
      }
      return 0;
    }
    int num_rows()const {
      return numRows;
    }
    int num_cols()const {
      return numRows;
    }


  private:

    //struct for a district
    struct Node{
      int data;
      Node *next;
      Node *prev;
    };

    struct District{
      int population;
      Node *membersFront;
      Node *membersBack;
      District() : population(0) {
        membersFront = nullptr;
        membersBack = nullptr;
      }
    };

    struct Person{
      int r,c;
      bool alive;
      Node *node;
      Person() : r(-1), c(-1), alive(false){
        node = nullptr;
      }
    };

    bool isValidCoor(int row, int col)const{
      if(row >= numRows || row < 0 || col >= numCols || col < 0)
        return false;
      return true;
    }

    void growArray(){
      int i;
      pplSize *= 2;
      Person *tempPeople = new Person[pplSize];
      for(i = 0; i < popul; i++){
        tempPeople[i].r = people[i].r;
        tempPeople[i].c = people[i].c;
        tempPeople[i].alive = people[i].alive;
        tempPeople[i].node = people[i].node;
      }
      delete people;
      people = tempPeople;
    }

    int numRows, numCols, popul, pplSize;
    Person *people;
    District **grid;
    District graveyard;

};
