#include "collidable.h"

double Collidable::getWidth(){
    return _width;
}
double Collidable::getHeight(){
    return _height;
}
double Collidable::getX(){
    return _x;
}
double Collidable::getY(){
    return _y;
}

void Collidable::setWidth(double width){
    _width = width;
}
void Collidable::setHeight(double height){
    _height = height;
}
void Collidable::setX(double x){
    _x = x;
}
void Collidable::setY(double y){
    _y = y;
}
void Collidable::setRotation(double rotation){
    _rotation = rotation;
}