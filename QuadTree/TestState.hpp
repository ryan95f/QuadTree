#ifndef __TEST_STATE_HPP
#define __TEST_STATE_HPP

#define POINT_WIDTH 5
#define N_SQUARES 60

#include "QuadTree.hpp"

class TestState
{
public:
	TestState();
	~TestState();

	void update(float dt);
	void render(sf::RenderWindow *window);

private:
	QuadTree *tree;
	sf::RectangleShape squares[N_SQUARES];
	sf::RectangleShape treeSquare;
};


#endif // __TEST_STATE_HPP