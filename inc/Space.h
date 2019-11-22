#ifndef SPACE_H
#define SPACE_H

#include<vector>
//SPACESTATES 1-8 is taken by nearby mine numbers as I felt this was better than using a seperate variable.
typedef enum SPACESTATES{HIDDEN = 9, EMPTY = 10, FLAG = 11, MINE = 12, EXPLODED = 13, QMARK = 14};

class Space{
    int spaceState;
    int nearbyMines;// not needed?
    bool mine;
    int x;
    int y;
public: 
    Space();
    Space(const Space& other);
    Space(int, int, bool);
//Setters
void setNearbyMines(int );
void setState(int );
void setMine(bool );

//Getters
int getState() const;
int getNearbyMines() const;
bool getMine() const;

//Functions
int minesNearby(std::vector<std::vector<Space>> , int , int );
};

#endif