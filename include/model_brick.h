#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "Collidable.h"

class BrickModel : public Collidable {
public:
    BrickModel(int width, int x, int y); // sets width and position of brick
    bool getIsRemoved(); // getter for isRemoved
    int isCollided(double x, double y);
    int getWidth();
    int getX();
    int getY();

private:
    bool isRemoved = false; // saves if the brick is removed
    int width;
    int x;
    int y;
};

#endif //BREAKOUT_BRICK_H
