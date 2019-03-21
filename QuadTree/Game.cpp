#include "Game.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

Game::Game() : state(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quad Tree");
}

Game::~Game() {}

void Game::handleInputs()
{
	sf::Event evnt;
	while(window.pollEvent(evnt))
	{
		if(evnt.type == sf::Event::Closed)
		{
			// close the window
			window.close();
		}
	}
}

void Game::update()
{
	float timestep = 1 / 120.0f;
	float elapsed = elapsed_time.asSeconds();

	// if the current game time has reach a "tick"
	// execute the state's update method.
	if(elapsed >= timestep)
	{
		state.update(timestep);
		elapsed_time -= sf::seconds(timestep);
	}
}

void Game::render()
{
	// clear the screen of all objects
	window.clear(sf::Color::Black);

	// draw to all objects to the buffer within the state
	state.render(&window);

	// display the drawn objects in the buffer
	window.display();
}

void Game::restartClock()
{
	// reset the game block
	elapsed_time += clock.restart();
}

bool Game::isOpen() const
{
	return window.isOpen();
}