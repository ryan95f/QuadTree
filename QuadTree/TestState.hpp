#ifndef __TEST_STATE_HPP
#define __TEST_STATE_HPP

#define N_SQUARES 100

#include "QuadTree.hpp"
#include "Point.hpp"

class TestState
{
public:
	TestState(int width, int height);
	~TestState();

	void update(float dt);
	void render(sf::RenderWindow *window);

private:
	const int width;
	const int height;

	QuadTree *tree;
	Point points[N_SQUARES];
	sf::RectangleShape point_square;
	sf::RectangleShape tree_square;
	PointVector *collisionVector;
};


#endif // __TEST_STATE_HPP