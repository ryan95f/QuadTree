#ifndef __QUADTREE_HPP
#define __QUADTREE_HPP

#include <SFML\Graphics.hpp>
#include <vector>

#define CHILD_LIMIT 4

class QuadTree
{
public:
	QuadTree(sf::FloatRect boundry);
	~QuadTree();

	void display(sf::RectangleShape *shape, sf::RenderWindow *target);

	bool insert(sf::CircleShape *circle);
	void subdivide();

private:
	std::vector<sf::CircleShape *> circles;

	sf::FloatRect boundry;

	QuadTree *top_left_child;
	QuadTree *top_right_child;
	QuadTree *bottom_left_child;
	QuadTree *bottom_right_child;
};

#endif // __QUADTREE_HPP