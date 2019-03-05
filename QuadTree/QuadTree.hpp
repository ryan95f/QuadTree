#ifndef __QUADTREE_HPP
#define __QUADTREE_HPP

#include <SFML\Graphics.hpp>
#include <vector>

#define CHILD_THRRESHOLD 4

class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry, int depth = 0);
	~QuadTree();

	void display(sf::RectangleShape *shape, sf::RenderWindow *target);
	bool insert(sf::RectangleShape *circle);

	void displayDepth() const;
	int maxDepth() const;
private:
	void subdivide();

	int depth;
	sf::FloatRect boundry;
	QuadTree *top_left_child;
	QuadTree *top_right_child;
	QuadTree *bottom_left_child;
	QuadTree *bottom_right_child;
	std::vector<sf::RectangleShape *> entities;
};

#endif // __QUADTREE_HPP