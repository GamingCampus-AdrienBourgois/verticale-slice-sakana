#include <iostream>
#include <random>
#include <time.h>

#include "../GameObjectLib/include/GameLoop.hpp"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	GameLoop game;
	game.run();
	return 0;
}
