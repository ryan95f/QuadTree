#include <cstdlib>
#include <ctime>

#include "TestState.hpp"

TestState::TestState(int width, int height) : width(width), height(height)
{
	float x = 0;
	float y = 0;

	// set the random seed
	// srand((unsigned int) time(NULL));

	tree = new QuadTree(sf::FloatRect(0, 0, (float) width, (float) height));

	for(int i = 0; i < N_SQUARES; ++i)
	{
		x = (float) (rand() % 600);
		y = (float) (rand() % 600);
		squares[i].setSize(sf::Vector2f(POINT_WIDTH, POINT_WIDTH));
		squares[i].setPosition(x, y);
		squares[i].setOrigin(POINT_WIDTH / 2.0f, POINT_WIDTH / 2.0f);
		tree->insert(&squares[i]);
	}

	treeSquare.setFillColor(sf::Color::Transparent);
	treeSquare.setOutlineColor(sf::Color::Blue);
	treeSquare.setOutlineThickness(1);
}

TestState::~TestState()
{
	if(tree != nullptr)
	{
		delete tree;
		tree = nullptr;
	}
}

void TestState::update(float dt)
{
	tree->clear();
	sf::Vector2f pos = sf::Vector2f(0, 0);
	for(int i = 0; i < N_SQUARES; ++i)
	{
		pos = squares[i].getPosition();
		pos.x += 20 * dt;
		squares[i].setPosition(pos);
		tree->insert(&squares[i]);
	}
}

void TestState::render(sf::RenderWindow *window)
{
	tree->display(&treeSquare, window);

	for(int i = 0; i < N_SQUARES; ++i)
	{
		window->draw(squares[i]);
	}
}