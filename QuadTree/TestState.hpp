#ifndef __TEST_STATE_HPP
#define __TEST_STATE_HPP

#define N_SQUARES 300

#include "QuadTree.hpp"
#include "Point.hpp"

/**
 * TestState is used to simulate and contain the game logic whilst testing
 * the quad tree for collision detection.
 */
class TestState
{
public:
	/**
	 * TestState constructor
	 * @param width - Width of the window
	 * @param height - Height of the window
	 */
	TestState(int width, int height);

	/**
	 * TestState deconstructor
	 */
	~TestState();

	/*============= Public Methods ==============*/

	/**
	 * Update the various objects within the state at each "tick".
	 * @param dt- Delta Time step that the game is running at.
	 */
	void update(float dt);

	/**
	 * Render the objects to the window
	 * @param window - Renderwindow to draw the objects on.
	 */
	void render(sf::RenderWindow *window);

private:
	/*============= Private Instance Variables ==============*/
	const int width;
	const int height;

	QuadTree *tree;
	Point points[N_SQUARES];
	sf::RectangleShape point_square;
	sf::RectangleShape tree_square;
	PointVector *collision_vector;
};


#endif // __TEST_STATE_HPP