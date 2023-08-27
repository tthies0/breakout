#include "paddle.h"

void Paddle::setPaddleSpeed(double speed){
    _speed = speed;
}
double Paddle::getPaddleSpeed(){
    return _speed;
}

int Paddle::handleCollision(){
    return 0;
}
