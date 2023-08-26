#include "brick.h"


int Brick::getState(){
    return _state;
}

void Brick::setState(int state){
    _state = state;
}

void Brick::handleCollision(){
    _state = 0;
}