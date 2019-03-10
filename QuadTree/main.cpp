#include "Game.hpp"

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
