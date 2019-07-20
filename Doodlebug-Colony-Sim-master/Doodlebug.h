#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Land.h"

//Doodlebug subclass
class Doodlebug: public Creature{//Creature superclass
  private:
    int daysStarving;//amount of days the doodlebug has gone without eating
  public:
    Doodlebug(char t, int r, int c, int i);
    ~Doodlebug();
    bool hunt(Land *ln, int *i);
    void incrDaysAlive();
    int getDaysStarving();
    void resetDaysStarving();
    void incrDayStarving();
};
#endif