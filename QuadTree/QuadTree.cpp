#include "QuadTree.hpp"

QuadTree::QuadTree(sf::FloatRect boundry) : boundry(boundry), top_left_child(nullptr), 
	top_right_child(nullptr), bottom_left_child(nullptr), bottom_right_child(nullptr)
{
	circles.resize(CHILD_LIMIT);
}

QuadTree::~QuadTree()
{
	if(top_left_child != nullptr)
	{
		delete top_left_child;
		top_left_child = nullptr;
	}

	if(top_right_child != nullptr)
	{
		delete top_right_child;
		top_right_child = nullptr;
	}

	if(bottom_left_child != nullptr)
	{
		delete bottom_left_child;
		bottom_left_child = nullptr;
	}

	if(bottom_right_child != nullptr)
	{
		delete bottom_right_child;
		bottom_right_child = nullptr;
	}
}

void QuadTree::display(sf::RectangleShape *shape, sf::RenderWindow *target)
{
	shape->setSize(sf::Vector2f(boundry.width, boundry.height));
	shape->setPosition(boundry.top, boundry.left);
	target->draw(*shape);

	if(top_left_child != nullptr)
	{
		top_left_child->display(shape, target);
	}

	if(top_right_child != nullptr)
	{
		top_right_child->display(shape, target);
	}

	if(bottom_left_child != nullptr)
	{
		bottom_left_child->display(shape, target);
	}

	if(bottom_right_child != nullptr)
	{
		bottom_right_child->display(shape, target);
	}
}

bool QuadTree::insert(sf::CircleShape *shape)
{
	sf::Vector2f shape_pos = shape->getPosition();
	if(!(boundry.left <= shape_pos.x && (boundry.left + boundry.width) >= shape_pos.x 
		&& boundry.top <= shape_pos.y && (boundry.top + boundry.height) >= shape_pos.y))
	{
		return false;
	}

	if(circles.size() <= CHILD_LIMIT && top_left_child == nullptr)
	{
		circles.emplace_back(shape);
		return true;
	}

	if(top_left_child == nullptr)
	{
		subdivide();
	}
	
	if(top_left_child->insert(shape)) { return true; }
	
	if(top_right_child->insert(shape)) { return true; }
	
	if(bottom_left_child->insert(shape)) { return true; }
	
	if(bottom_right_child->insert(shape)) { return true; }

	return false;
}

void QuadTree::subdivide()
{
	float width = boundry.width / 2.0f;
	float height = boundry.height / 2.0f;

	sf::FloatRect top_left = sf::FloatRect(boundry.left, boundry.top, width, height);
	sf::FloatRect top_right = sf::FloatRect((boundry.left + width), boundry.top, width, height);
	sf::FloatRect bottom_left = sf::FloatRect(boundry.left, (boundry.top + height), width, height);
	sf::FloatRect bottom_right = sf::FloatRect((boundry.left + width), (boundry.top + height), width, height);

	top_left_child = new QuadTree(top_left);
	top_right_child = new QuadTree(top_right);
	bottom_left_child = new QuadTree(bottom_left);
	bottom_right_child = new QuadTree(bottom_right);
}
