#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.hpp"
#include "QuadTree.hpp"


#define POINT_WIDTH 5
#define N_SQUARES 60
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
	Game game;
	while(game.isOpen())
	{
		game.handleInputs();
		game.update();
		game.render();
		game.restartClock();
	}
	return 0;
}
