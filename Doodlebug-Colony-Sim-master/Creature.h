#ifndef CREATURE_H
#define CREATURE_H

#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>

//Creature class is the superclass of the Ant and Doodlebug class
class Creature{
  private:
    char type;
  protected:
    int daysAlive;
    int row;
    int col;
    int index;
    bool moved;
  public:
    Creature(char t, int r, int c, int i);
    ~Creature();
    char getType();
    void setMoved(bool m);
    bool getMoved();
    void setCoor(int x, int y);
    int getRow();
    int getCol();
    virtual void incrDaysAlive();
    int getDaysAlive();
    void resetDaysAlive();
    int getIndex();
    void move(int*x, int*y);
};

#endif