#ifndef BREAKOUT_MODEL_PADDLE_H
#define BREAKOUT_MODEL_PADDLE_H

#include "collidable.h"

class Paddle : public Collidable{
public:
    Paddle(double width, double height, double x, double y, double rotation)
        : Collidable(width,height,x,y,rotation){};
    double getPaddleSpeed();
    void setPaddleSpeed(double speed);

private:
    double _speed = 2; 
};

#endif //BREAKOUT_MODEL_PADDLE_H
