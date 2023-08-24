#include "ball.h"

Ball::Ball(double x, double y, double direction, double speed)
    :_x(x), _y(y), _direction(direction), _speed(speed) {}

double Ball::getX(){
    return _x;
}

double Ball::getY(){
    return _y;
}

double Ball::getDirection(){
    return _direction;
}

double Ball::getSpeed(){
    return _speed;
}

void Ball::setX(double x){
    _x = x;
}

void Ball::setY(double y){
    _y = y;
}

void Ball::setDirection(double direction){
    _direction = direction;
}

void Ball::setSpeed(double speed){
    _speed = speed;
}