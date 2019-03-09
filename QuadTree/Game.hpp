#ifndef __GAME_HPP
#define __GAME_HPP

#include <SFML\Graphics.hpp>
#include "TestState.hpp"

class Game
{
public:
	Game();
	~Game();

	void handleInputs();
	void update();
	void render();
	void restartClock();

	bool isOpen() const;

private:
	sf::Clock clock;
	sf::Time elapsed_time;
	sf::RenderWindow window;
	TestState state;
};

#endif // __GAME_HPP