#include "Land.h"

//Constructor for the land class
Land::Land(GridDisplay *grid){
  int i, j;
  gd = grid;
  rows = 20;
  cols = 20;
  location = new Creature**[rows];//2-D array of bugs for information keeping
  for(i = 0; i < rows; i++){
    location[i] = new Creature*[cols];
    for(j = 0; j < cols; j++)
      location[i][j] = NULL;
  }
}

int Land::getRows(){
  return rows;
}
int Land::getCols(){
  return cols;
}
//checks if the coordinate is within the grid bounds
bool Land::isValid(int r, int c){
  if((r >= 0 && r < rows) && (c >= 0 && c < cols))
    return true;
  return false;
}
//checks if the coordinate is occupied by a bug
bool Land::isOccupied(int r, int c){
  if(location[r][c] == NULL)
    return false;
  return true;
}
//adds a creature to the array contaning the location
bool Land::addCreature(Creature* cr, int r, int c){
  if(!isValid(r,c) || isOccupied(r,c))//check for valid coordinates
    return false;
  location[r][c] = cr;
  gd->setChar(r,c,cr->getType());//edit the grid board to represent the bug type
  return true;
}
//moves a bug to a specified location
bool Land::moveCreature(int xI, int yI, int xF, int yF){
  if(!isValid(xI,yI) || !isValid(xF,yF))//check for valid coordinates
    return false;
  location[xF][yF] = NULL;
  location[xF][yF] = location[xI][yI];//set new location
  location[xI][yI] = NULL;
  gd->setChar(xI,yI, '.');//modify the grid for output
  gd->setChar(xF,yF, getCreatureType(xF,yF));
  return true;
}

char Land::getCreatureType(int r, int c){
  return location[r][c]->getType();
}
//returns the index value for deallocation
int Land::getCreatureIndex(int r, int c){
  return location[r][c]->getIndex();
}
//spawns a new creature into the land
bool Land::spawnCreature(Creature *cr, int* x, int* y){
  int row = cr->getRow();
  int col = cr->getCol();
  //go through each adjacent points to find an open spot
  if(isValid(row+1, col) && isOccupied(row+1,col) == false){
    *x = row+1;
    *y = col;
    return true;
  }else if(isValid(row-1, col) && isOccupied(row-1,col) == false){
    *x = row-1;
    *y = col;
    return true;
  }else if(isValid(row, col+1) && isOccupied(row,col+1) == false){
    *x = row;
    *y = col+1;
    return true;
  }else if(isValid(row, col-1) && isOccupied(row,col-1) == false){
    *x = row;
    *y = col-1;
    return true;
  }
  return false;
}