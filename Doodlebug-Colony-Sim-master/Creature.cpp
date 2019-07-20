#include "Creature.h"

//Creature constructor
Creature::Creature(char t, int r, int c, int i){
  daysAlive = 0;
  row = r;
  col = c;
  index = i;
  moved = false;
  type = t;
}
//Creature destructor
Creature::~Creature(){ }
//returns the character type for each creature ('A' or 'D')
char Creature::getType(){
  return type;
}
//sets the moved boolean to a custom value
void Creature::setMoved(bool m){
  moved = m;
}

bool Creature::getMoved(){
  return moved;
}

void Creature::setCoor(int x, int y){
  row = x;
  col = y;
}

int Creature::getRow() {
  return row;
}

int Creature::getCol(){
  return col;
}
//virtual method
void Creature::incrDaysAlive(){ }

void Creature::resetDaysAlive(){
  daysAlive = 0;
}

int Creature::getDaysAlive(){
  return daysAlive;
}
//returns the value of the index location in the bugs class in main
int Creature::getIndex(){
  return index;
}
//process the move by randomly choosing a point adjacent
void Creature::move(int* x, int* y){
  int direction = rand() % 4;
  if(direction == 0){
    *x = row;
    *y = col-1;
  }else if(direction == 1){
    *x = row;
    *y = col+1;
  }else if(direction == 2){
    *x = row-1;
    *y = col;
  }else{
    *x = row+1;
    *y = col;
  }
  moved = true;
}