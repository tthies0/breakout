#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "Collidable.h"

class Brick : public Collidable {
public:
    enum BrickState{broken, normal};
    Brick(double width, double height, double x, double y, BrickState state = normal) : Collidable(width, height, x, y){}; // sets width and position of brick
    
    BrickState getState();
    void setState(BrickState state);

private:
    BrickState _state;
};

#endif //BREAKOUT_BRICK_H
