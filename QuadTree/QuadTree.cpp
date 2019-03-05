#include <iostream>
#include "QuadTree.hpp"

#define DEPTH_ARRAY_SIZE 4

QuadTree::QuadTree(sf::FloatRect boundry, int depth) : boundry(boundry), depth(depth), top_left_child(nullptr), 
	top_right_child(nullptr), bottom_left_child(nullptr), bottom_right_child(nullptr) {}

QuadTree::~QuadTree()
{
	// Delete each child branch if not a null pointer
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
	shape->setPosition(boundry.left, boundry.top);
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

bool QuadTree::insert(sf::RectangleShape *shape)
{
	sf::FloatRect shape_rect = shape->getGlobalBounds();
	if(!boundry.intersects(shape_rect))
	{
		return false;
	}

	if(entities.size() < CHILD_THRRESHOLD && top_left_child == nullptr)
	{
		entities.emplace_back(shape);
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

void QuadTree::displayDepth() const
{
	std::cout << "Depth: " << depth << " " << entities.size() << std::endl;

	if(top_left_child != nullptr)
	{
		top_left_child->displayDepth();
	}

	if(top_right_child != nullptr)
	{
		top_right_child->displayDepth();
	}

	if(bottom_left_child != nullptr)
	{
		bottom_left_child->displayDepth();
	}
	
	if(bottom_right_child != nullptr)
	{
		bottom_right_child->displayDepth();
	}
}

int QuadTree::maxDepth() const
{
	int i = 0;
	int largest = depth;
	int depths[DEPTH_ARRAY_SIZE] = {0, 0, 0, 0};

	// get the max depth from the top left child
	if(top_left_child != nullptr)
	{
		depths[0] = top_left_child->maxDepth();
	}

	// get the max depth from top right child
	if(top_right_child != nullptr)
	{
		depths[1] = top_right_child->maxDepth();
	}

	// get the max depth from bottom left child
	if(bottom_left_child != nullptr)
	{
		depths[2] = bottom_left_child->maxDepth();
	}
	
	// get the max depth from bottom right child
	if(bottom_right_child != nullptr)
	{
		depths[3] = bottom_right_child->maxDepth();
	}

	// loop through array and check that current
	// depth is not smaller than those from the child branches.
	for(i = 0; i < DEPTH_ARRAY_SIZE; ++i)
	{
		// if the largest is less than the current
		// depth, make the depth the new largest.
		if(largest < depths[i])
		{
			largest = depths[i];
		}
	}
	return largest;
}

void QuadTree::subdivide()
{
	int next_depth = (depth + 1);

	// calculate the new width and height
	float width = boundry.width / 2.0f;
	float height = boundry.height / 2.0f;	

	// calculate the boundries for the child nodes
	sf::FloatRect top_left = sf::FloatRect(boundry.left, boundry.top, width, height);
	sf::FloatRect top_right = sf::FloatRect((boundry.left + width), boundry.top, width, height);
	sf::FloatRect bottom_left = sf::FloatRect(boundry.left, (boundry.top + height), width, height);
	sf::FloatRect bottom_right = sf::FloatRect((boundry.left + width), (boundry.top + height), width, height);

	// create the child nodes
	top_left_child = new QuadTree(top_left, next_depth);
	top_right_child = new QuadTree(top_right, next_depth);
	bottom_left_child = new QuadTree(bottom_left, next_depth);
	bottom_right_child = new QuadTree(bottom_right, next_depth);

	// move the entities to the newly created leaf nodes
	while(entities.begin() != entities.end())
	{
		// move the references to the leaf node
		insert(*entities.begin());

		// discard reference from this layer in the tree
		entities.erase(entities.begin());
	}

}
