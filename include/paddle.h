#ifndef BREAKOUT_MODEL_PADDLE_H
#define BREAKOUT_MODEL_PADDLE_H

#include "collidable.h"

class Paddle : public Collidable{
public:
    Paddle(double width, double height, double x, double y, double rotation, double speed)
        : Collidable(width,height,x,y,rotation), _speed(speed){};
    double getPaddleSpeed();
    void setPaddleSpeed(double speed);
    virtual void handleCollision();

private:
    double _speed; 
};

#endif //BREAKOUT_MODEL_PADDLE_H
