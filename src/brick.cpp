#include "brick.h"


int Brick::getState(){
    return _state;
}

void Brick::setState(int state){
    _state = state;
}

int Brick::handleCollision(){
    int returnValue = 0;
    if(_state==2){
        _state = 1;
        return 2;
    }
    returnValue = _state;
    _state = 0;
    return returnValue;
}