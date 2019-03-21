#ifndef __QUADTREE_HPP
#define __QUADTREE_HPP

#include <SFML\Graphics.hpp>
#include <vector>

#include "Point.hpp"

#define CHILD_THRRESHOLD 4

typedef std::vector<Point *> PointVector;

/**
 * QuadTree - A spatial data structure for tracking objects across an area.
 * In this case, it is being used to track objects within a window for collision detection.
 */
class QuadTree
{
public:

	/**
	 * Quad Tree constructor
	 * @param boundry - The spacial boundry for this quad.
	 * @param depth - The depth level for this quad node.
	 */
	QuadTree(sf::FloatRect boundry, int depth = 0);

	/**
	 * Quad Tree deconstructor
	 */
	~QuadTree();


	/*============= Public Methods ==============*/

	/**
	 * Gets the number of points that a search area is intersecting
	 * over one or more quads within a 2D space.
	 * @param search_area - The area to look for points
	 * @return the number of points within the search area.
	 */
	int getPointsInArea(sf::FloatRect search_area);
	
	/**
	 * Checks that a search area is intersecting with one or more points.
	 * @param search_area - The area to look for a intersections.
	 * @return True if the area is intersecting with points. False if its not.
	 */
	bool isIntersecting(sf::FloatRect search_area);

	/**
	 * clears the quad tree of all children
	 */
	void clear();

	/**
	 * Inserts a new point into the quad tree.
	 * @param point - Pointer to to a point object. Note that the quad tree is not
	 *				  responsible for releasing the memory of any point object.
	 * @return true if successfully inserted, false if it cannot.
	 */
	bool insert(Point *point);

	/**
	 * Gets the max depth of the quad tree.
	 * @returns the depth of the quad tree.
	 */
	int maxDepth() const;

	/**
	 * Gets all the points that a search area is intersecting quad so collision
	 * detection can be used on each point.
	 * @param search - The area to look for points.
	 * @return A vector of point references with candidate objects that could be
	 * colliding with the search area. 
	 */
	PointVector * retrieve(PointVector * returnList, sf::FloatRect search);

	/**
	 * Renders the quad tree on the view window
	 * @param shape - Pointer to rectangle shape that will be used to visualize each quad.
	 * @param target - Pointer to render window which the quad tree will be visualized on. 
	 */
	void display(sf::RectangleShape *shape, sf::RenderWindow *target);
private:
	/*============= Private Methods ==============*/

	/**
	 * Divides the quad into 4 more quads when the child threshold has been reached.
	 */
	void subdivide();

	/*============= Private Instance Variables ==============*/
	int depth;
	sf::FloatRect boundry;
	QuadTree *top_left_child;
	QuadTree *top_right_child;
	QuadTree *bottom_left_child;
	QuadTree *bottom_right_child;
	PointVector entities;
};

#endif // __QUADTREE_HPP