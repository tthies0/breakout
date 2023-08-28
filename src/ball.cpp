#include "ball.h"

Ball::Ball(double x, double y, double directionX, double directionY, double speed)
    :_x(x), _y(y), _directionX(directionX), _directionY(directionY), _speed(speed) {}

double Ball::getX(){
    return _x;
}

double Ball::getY(){
    return _y;
}

double Ball::getDirectionX(){
    return _directionX;
}

double Ball::getDirectionY(){
    return _directionY;
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

void Ball::setDirectionX(double direction){
    _directionX = direction;
}

void Ball::setDirectionY(double direction){
    _directionY = direction;
}

void Ball::setSpeed(double speed){
    _speed = speed;
}