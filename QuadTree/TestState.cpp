#include <cstdlib>
#include <ctime>

#include "TestState.hpp"

TestState::TestState(int width, int height) : width(width), height(height)
{
	float x = 0;
	float y = 0;

	// set the random seed
	srand((unsigned int) time(NULL));

	tree = new QuadTree(sf::FloatRect(0, 0, (float) width, (float) height));

	// set up the points and insert them into the initial tree.
	for(int i = 0; i < N_SQUARES; ++i)
	{
		// generate the x and y coordinates
		x = (float) (rand() % width);
		y = (float) (rand() % height);
		points[i].pos = sf::Vector2f(x, y);
		tree->insert(&points[i]);
	}

	// set up the square for visualizing a point
	point_square.setFillColor(sf::Color::White);
	point_square.setSize(sf::Vector2f(POINT_WIDTH, POINT_HEIGHT));
	point_square.setOrigin(POINT_WIDTH / 2.0f, POINT_HEIGHT / 2.0f);

	// set up the square for visualising the quad tree
	tree_square.setFillColor(sf::Color::Transparent);
	tree_square.setOutlineColor(sf::Color::Blue);
	tree_square.setOutlineThickness(1);
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
	Point *point = nullptr;
	sf::Vector2f pos = sf::Vector2f(0, 0);
	sf::Vector2f increment = sf::Vector2f(0, 0);

	// clear the tree so it can updated
	tree->clear();
	
	// loop through the points and update their position.
	for(int i = 0; i < N_SQUARES; ++i)
	{
		point = &points[i];
		increment = point->increment;
		pos = point->pos;

		// check that the point has gone past the x boundry
		if((pos.x > width && increment.x > 0) || (pos.x < 0 && increment.x < 0))
		{
			// bounce the point in the opposite y direction
			point->increment.x = -increment.x;
		}

		// check that the point has gone past the y boundry 
		if((pos.y > height && increment.y > 0) || (pos.y < 0 && increment.y < 0))
		{
			// bounce the point in the opposite y direction
			point->increment.y = -increment.y;
		}

		// update the posistion
		point->pos = (pos + increment);
		
		// insert the point back into the tree
		tree->insert(point);
	}
}

void TestState::render(sf::RenderWindow *window)
{
	// draw the quad tree
	tree->display(&tree_square, window);

	// draw the points
	for(int i = 0; i < N_SQUARES; ++i)
	{
		point_square.setPosition(points[i].pos);
		window->draw(point_square);
	}
}