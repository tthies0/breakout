#include "paddle.h"

void Paddle::setPaddleSpeed(double speed){
    _speed = speed;
}
double Paddle::getPaddleSpeed(){
    return _speed;
}

void Paddle::handleCollision(){
    this->setY(this->getY()+1);
}
