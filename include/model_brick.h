#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "Collidable.h"

class BrickModel : public Collidable {
public:
    BrickModel(int width, int x, int y); // sets width and position of brick
    bool getIsRemoved(); // getter for isRemoved

private:
    bool isRemoved = false; // saves if the brick is removed
};

#endif //BREAKOUT_BRICK_H
