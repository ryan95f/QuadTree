#include <cstdlib>
#include <ctime>

#include <iostream>
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

	collisionVector = new PointVector;
}

TestState::~TestState()
{
	// Deallocate the Quad Tree
	if(tree != nullptr)
	{
		delete tree;
		tree = nullptr;
	}

	// Deallocate the collision vector
	if(collisionVector != nullptr)
	{
		delete collisionVector;
		collisionVector = nullptr;
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

	// loop through all the points to check there is a collision
	for(int i = 0; i < N_SQUARES; ++i)
	{
		// get the bounds of the current point and extract all points that are in its quad.
		sf::FloatRect bounds = points[i].getGlobalBounds();
		tree->retrieve(collisionVector, bounds);

		// loop through all points in the quad and check that the current
		// point could have collided with another point. 
		// Max entities in the vector is based on the Quad Tree threshold.
		for(Point *p : *collisionVector)
		{
			// Use AABB collision detection
			if(bounds.intersects(p->getGlobalBounds()))
			{
				// resolve the collision for the current point.
				points[i].resolveCollision();
			}
		}

		// clear the collision vector so we can reuse it with the next lot of entities
		// If this isn't clear, then a point will just get stuck.
		collisionVector->clear();
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