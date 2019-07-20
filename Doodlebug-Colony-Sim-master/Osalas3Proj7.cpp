#include "Land.h"
#include "Ant.h"
#include "Doodlebug.h"

int main(int argc, char *argv[]){

  int l;
  int delay = 1000;//get command line argument for delay
  for(l = 0;l < argc; l++){
    if('-' == argv[l][0] && 'd' == argv[l][1]){
      delay = atoi(argv[2]);
      printf("Custome amount: %d\n", delay);
    }
  }


  srand(time(NULL));
  GridDisplay grid;
  Land land(&grid);
  int days = 0;
  int numAnts = 100;
  int numDoodlebugs = 5;
  int i, row, col, index, k;
  int moveX = 0;
  int moveY = 0;
  int spawnX = 0;
  int spawnY = 0;

  
  Creature** bugs;//array of bugs
  bugs = new Creature*[400];
  for(i = 0; i < (numAnts+numDoodlebugs); i++){//populate the array
    do{//random coordniates
      row = rand() % land.getRows();
      col = rand() % land.getCols();
    }while(land.isValid(row,col) == false || land.isOccupied(row,col) == true);
    if(i < 100){//100 ants
      bugs[i] = new Ant('A',row,col,i);
    }else if(i > 99 && i < 105){//5 doodlebugs
      bugs[i] = new Doodlebug('D',row,col,i);
    }else{
      bugs[i] = NULL;
    }
    land.addCreature(bugs[i],row,col);
  }
  grid.showGrid();
  while(days < 20){
    days++;
    // Doodlebugs move first
    for(i = 0; i < 400; i++){
      //find all the doodlebugs
      if(bugs[i] != NULL && bugs[i]->getType() == 'D' && bugs[i]->getMoved() == false){
        //hunt for ants
        //cast as doodlebug since array is polymorphic
        if((dynamic_cast<Doodlebug*>(bugs[i]))->hunt(&land,&index)){
          delete bugs[index];//deallocate memory for the ant
          bugs[index] = NULL;
          dynamic_cast<Doodlebug*>(bugs[i])->resetDaysStarving();
        }else{//atempt to move the doodlebug to a new location
          dynamic_cast<Doodlebug*>(bugs[i])->incrDayStarving();
          bugs[i]->move(&moveX, &moveY);
          //valid and unoccupied coordinates in the grid
          if(land.isValid(moveX,moveY) && land.isOccupied(moveX, moveY) == false){
            land.moveCreature(bugs[i]->getRow(), bugs[i]->getCol(), moveX, moveY);
            bugs[i]->setCoor(moveX, moveY);
          }

        }
        //Atempt to spawn a new doodlebug 
        dynamic_cast<Doodlebug*>(bugs[i])->incrDaysAlive();
        if(bugs[i]->getDaysAlive() >= 8 && land.spawnCreature(bugs[i],&spawnX, &spawnY)){
          //find an open slot in the array
          for(k = 0; k < 400; k++){
            if(bugs[k] == NULL){
              //spawns a new doodlebug near the parent
              bugs[k] = new Doodlebug('D', spawnX, spawnY,k);
              bugs[k]->setMoved(true);
              land.addCreature(bugs[k], spawnX, spawnY);  
              bugs[i]->resetDaysAlive();      
              break;
            }
          }
        }
        //Starve the doodlebug
        if(dynamic_cast<Doodlebug*>(bugs[i])->getDaysStarving() == 3){
          grid.setChar(bugs[i]->getRow(),bugs[i]->getCol(),'.');
          //deallocate memory for the dead doodlebug
          delete bugs[i];
          bugs[i] = NULL;
          break;
        }
        bugs[i]->setMoved(true);
      }
    }
    //Ants move second
    for(i = 0; i < 400; i++){
      //Find all the ants in the array
      if(bugs[i] != NULL && bugs[i]->getType() == 'A' && bugs[i]->getMoved() == false){
        //Atempt to move the ant to a new location
        bugs[i]->move(&moveX, &moveY);
        if(land.isValid(moveX,moveY) && land.isOccupied(moveX, moveY) == false){
          land.moveCreature(bugs[i]->getRow(), bugs[i]->getCol(), moveX, moveY);
          bugs[i]->setCoor(moveX, moveY);
        }
        //Atempt to spawn a new ant
        dynamic_cast<Ant*>(bugs[i])->incrDaysAlive();
        if(bugs[i]->getDaysAlive() >= 3 && land.spawnCreature(bugs[i],&spawnX, &spawnY)){
          //Find an open spot in the array
          for(k = 0; k < 400; k++){
            if(bugs[k] == NULL){
              bugs[k] = new Ant('A', spawnX, spawnY,k);
              bugs[k]->setMoved(true);
              land.addCreature(bugs[k], spawnX, spawnY);
              bugs[i]->resetDaysAlive();    
              break;
            }
          }
        }
        bugs[i]->setMoved(true);
      }  
    }

    for(i = 0; i < 400; i++){
      if(bugs[i] != NULL){
        bugs[i]->setMoved(false);
      }
    }
    //sleep the terminal and display the grid
    grid.mySleep(delay);
    grid.showGrid();
  }
  return 0;
}