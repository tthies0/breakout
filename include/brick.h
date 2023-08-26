#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "collidable.h"

class Brick : public Collidable {
public:
    enum BrickState{broken, normal};
    Brick(double width, double height, double x, double y, double rotation, BrickState state = normal) : Collidable(width, height, x, y, rotation){}; // sets width and position of brick
    
    virtual void handleCollision();
    BrickState getState();
    void setState(BrickState state);

private:
    BrickState _state;
};

#endif //BREAKOUT_BRICK_H
