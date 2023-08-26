#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "collidable.h"

class Brick : public Collidable {
public:
    enum BrickState{broken, normal};
    Brick(double width, double height, double x, double y, double rotation, int state) : Collidable(width, height, x, y, rotation), _state(state){}; // sets width and position of brick
    
    virtual void handleCollision();
    int getState();
    void setState(int state);

private:
    int _state;
};

#endif //BREAKOUT_BRICK_H
