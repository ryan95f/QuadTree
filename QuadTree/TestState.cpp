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
		points[i].pos = sf::Vector2f(x, y);
		tree->insert(&points[i]);
	}

	point_square.setFillColor(sf::Color::White);
	point_square.setSize(sf::Vector2f(POINT_WIDTH, POINT_HEIGHT));
	point_square.setOrigin(POINT_WIDTH / 2.0f, POINT_HEIGHT / 2.0f);

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
	Point *point = nullptr;
	sf::Vector2f pos = sf::Vector2f(0, 0);
	sf::Vector2f increment = sf::Vector2f(0, 0);
	for(int i = 0; i < N_SQUARES; ++i)
	{
		point = &points[i];
		increment = point->increment;
		pos = point->pos;

		if((pos.x > width && increment.x > 0) || (pos.x < 0 && increment.x < 0))
		{
			point->increment.x = -increment.x;
		}

		if((pos.y > height && increment.y > 0) || (pos.y < 0 && increment.y < 0))
		{
			point->increment.y = -increment.y;
		}
		point->pos = (pos + increment);
		tree->insert(point);
	}
}

void TestState::render(sf::RenderWindow *window)
{
	tree->display(&treeSquare, window);

	for(int i = 0; i < N_SQUARES; ++i)
	{
		point_square.setPosition(points[i].pos);
		window->draw(point_square);
	}
}