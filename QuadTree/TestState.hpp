#ifndef __TEST_STATE_HPP
#define __TEST_STATE_HPP

#define POINT_WIDTH 5
#define N_SQUARES 30

#include "QuadTree.hpp"

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
	sf::RectangleShape squares[N_SQUARES];
	sf::RectangleShape treeSquare;
};


#endif // __TEST_STATE_HPP