#include "GameLoop.hpp"
#include <iostream>
#include <time.h>
#include <random>

int main() {
    srand(time(NULL));
    GameLoop game;
    game.run();
    return 0;
}






