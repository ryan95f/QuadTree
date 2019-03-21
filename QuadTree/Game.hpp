#ifndef __GAME_HPP
#define __GAME_HPP

#include <SFML\Graphics.hpp>
#include "TestState.hpp"

class Game
{
public:

	/**
	 * Game constructor
	 */
	Game();

	/**
	 * Game deconstructor
	 */
	~Game();

	/*============= Public Methods ==============*/

	/**
	 * Handles the user's input during the game.
	 */
	void handleInputs();

	/**
	 * Updates all objects that are currently in use during the game.
	 */
	void update();

	/**
	 * Draws all objects onto the window
	 */
	void render();

	/**
	 * Resets the games time after each iteration.
	 */
	void restartClock();

	/**
	 * Method to determine if the window is open or closed.
	 * @return True if open. False if called.
	 */
	bool isOpen() const;

private:
	/*============= Private Instance Variables ==============*/

	sf::Clock clock;
	sf::Time elapsed_time;
	sf::RenderWindow window;
	TestState state;
};

#endif // __GAME_HPP