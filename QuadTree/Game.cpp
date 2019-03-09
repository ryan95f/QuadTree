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
			window.close();
		}
	}
}

void Game::update()
{
	float timestep = 1 / 120.0f;
	float elapsed = elapsed_time.asSeconds();

	if(elapsed >= timestep)
	{
		state.update(timestep);
		elapsed_time -= sf::seconds(timestep);
	}
}

void Game::render()
{
	window.clear(sf::Color::Black);
	state.render(&window);
	window.display();
}

void Game::restartClock()
{
	elapsed_time += clock.restart();
}

bool Game::isOpen() const
{
	return window.isOpen();
}