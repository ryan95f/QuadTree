#ifndef __QUADTREE_HPP
#define __QUADTREE_HPP

#include <SFML\Graphics.hpp>
#include <vector>

#include "Point.hpp"

#define CHILD_THRRESHOLD 4

class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry, int depth = 0);
	~QuadTree();

	int search(sf::FloatRect search_area);
	bool collisions(sf::FloatRect search_area);

	void clear();

	bool insert(Point *point);
	int maxDepth() const;

	void displayDepth() const;
	void display(sf::RectangleShape *shape, sf::RenderWindow *target);
private:
	void subdivide();

	int depth;
	sf::FloatRect boundry;
	QuadTree *top_left_child;
	QuadTree *top_right_child;
	QuadTree *bottom_left_child;
	QuadTree *bottom_right_child;
	std::vector<Point *> entities;
};

#endif // __QUADTREE_HPP