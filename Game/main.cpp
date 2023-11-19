#include "GameLoop.hpp"
#include <iostream>
#include <time.h>
#include <random>

int main() 
{
    srand(static_cast<unsigned int>(time(NULL)));
    GameLoop game;
    game.run();
    return 0;
}






