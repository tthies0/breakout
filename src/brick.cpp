#include "brick.h"

Brick::Brick(double width, double height, double x, double y, BrickState state = normal)
    :Collidable(width, height, x ,y), _state(state){
}

Brick::BrickState Brick::getState(){
    return _state;
}