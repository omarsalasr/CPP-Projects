#ifndef ANT_H
#define ANT_H

#include "Creature.h"

//Ant subclass
class Ant: public Creature{//Creature superclass
  public:
    Ant(char t, int r, int c, int i);
    ~Ant();
    void incrDaysAlive();
};

#endif