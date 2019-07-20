#include "Doodlebug.h"

//Doodlebug constructor which calls the creature constructor
Doodlebug::Doodlebug(char t, int r, int c, int i) : Creature(t,r,c,i){ }
//Doodlebug destructor
Doodlebug::~Doodlebug(){ }

//checks to see if the doodlebug can eat a nearby ant
bool Doodlebug::hunt(Land *ln, int *i){
  //checks if the adjacent spots are valid and occupied by an Ant
  if(ln->isValid(row+1, col) && ln->isOccupied(row+1,col) && ln->getCreatureType(row+1,col) == 'A'){
    moved = true;
    *i = ln->getCreatureIndex(row+1,col);//returns the index of the ant for deallocation
    ln->moveCreature(row,col,row+1,col);//calls the move creature function to process the new coordinates
    row = row+1;
    daysStarving = 0;
    return true;
  }if(ln->isValid(row-1, col) && ln->isOccupied(row-1,col) && ln->getCreatureType(row-1,col) == 'A'){
    moved = true;
    *i = ln->getCreatureIndex(row-1,col);
    ln->moveCreature(row,col,row-1,col);
    row = row-1;
    daysStarving = 0;
    return true;
  }if(ln->isValid(row, col+1) && ln->isOccupied(row,col+1) && ln->getCreatureType(row,col+1) == 'A'){
    moved = true;
    *i = ln->getCreatureIndex(row,col+1);
    ln->moveCreature(row,col,row,col+1);
    col = col+1;
    daysStarving = 0;
    return true;
  }if(ln->isValid(row, col-1) && ln->isOccupied(row,col-1) && ln->getCreatureType(row,col-1) == 'A'){
    moved = true;
    *i = ln->getCreatureIndex(row,col-1);
    ln->moveCreature(row,col,row,col-1);
    col = col-1;
    daysStarving = 0;
    return true;
  }
  return false;
}

void Doodlebug::incrDaysAlive(){
  daysAlive++; 
}

int Doodlebug::getDaysStarving(){
  return daysStarving;
}

void Doodlebug::resetDaysStarving(){
  daysStarving = 0;
}

void Doodlebug::incrDayStarving(){
  daysStarving++;
}