#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.hpp"
#include "QuadTree.hpp"

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
