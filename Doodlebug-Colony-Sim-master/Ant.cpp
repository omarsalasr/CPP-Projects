#include "Ant.h"

//Constructor for the Ant class which calls the Creature superclass
Ant::Ant(char t, int r, int c, int i) : Creature(t,r,c,i){ }
//Destructor for the Ant class
Ant::~Ant(){ }
//Increment the days alive for the ant
void Ant::incrDaysAlive(){
  daysAlive++;
}