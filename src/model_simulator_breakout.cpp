#include "model_simulator_breakout.h"
#include <ncurses.h>
#include <stdlib.h>

BreakoutModel::BreakoutModel() {
};


int BreakoutModel::getGameWidth() {
    return width; 
};
    
int BreakoutModel::getGameHeight() {
    return height; 
};
    

void BreakoutModel::simulate_game_step()
{
    // Implement game dynamics.
    notifyUpdate();
};