#ifndef LAND_H
#define LAND_H

#include "Creature.h"
#include "GridDisplay.h"

class Land{
  private:
    Creature* **location;//2-D array of creatures to keep track of the location on the grid
    int rows;
    int cols;
    GridDisplay *gd;//grid pointer to modify the grid for output
  public:
    Land(GridDisplay *grid);
    int getRows();
    int getCols();
    bool isValid(int r, int c);
    bool isOccupied(int r, int c);
    bool addCreature(Creature* cr, int r, int c);
    bool moveCreature(int xI, int yI, int xF, int yF);
    char getCreatureType(int r, int c);
    int getCreatureIndex(int r, int c);
    bool spawnCreature(Creature *cr, int* x, int* y);
};
#endif