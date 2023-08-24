#include "collidable.h"

Collidable::Collidable(double width, double height, double x, double y)
    :_width(width), _height(height), _x(x), _y(y){}

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