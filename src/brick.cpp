#include "brick.h"


Brick::BrickState Brick::getState(){
    return _state;
}

void Brick::setState(BrickState state){
    _state = state;
}

void Brick::handleCollision(){
    _state = Brick::broken;
}