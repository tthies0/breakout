#include "model_simulator_breakout.h"
#include <ncurses.h>
#include <stdlib.h>

BreakoutModel::BreakoutModel() {
};

void BreakoutModel::simulate_game_step()
{
    // Implement game dynamics.
    notifyUpdate();
};