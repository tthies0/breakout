#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "collidable.h"

class Brick : public Collidable {
public:
    enum BrickState{broken, normal};
    Brick(double width, double height, double x, double y, double rotation, int state) : Collidable(width, height, x, y, rotation), _state(state){}; // sets width and position of brick
    
    virtual int handleCollision();
    int getState();
    void setState(int state);

private:
    //Unfortunately enums didnt work here
    int _state; // 0 = broken, 1 = normal, 2 = hitTwice, 3 = addBall
};

#endif //BREAKOUT_BRICK_H
