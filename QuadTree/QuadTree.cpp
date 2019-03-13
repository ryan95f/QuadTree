#include <iostream>
#include "QuadTree.hpp"

#define DEPTH_ARRAY_SIZE 4

QuadTree::QuadTree(sf::FloatRect boundry, int depth) : boundry(boundry), depth(depth), top_left_child(nullptr), 
	top_right_child(nullptr), bottom_left_child(nullptr), bottom_right_child(nullptr) {}

QuadTree::~QuadTree()
{
	clear();
}

int QuadTree::search(sf::FloatRect search_area)
{
	int count = 0;

	// if the search area is not in curent quad, return 0 for no entities.
	if(!boundry.intersects(search_area))
	{
		return 0;
	}

	// if not a leaft node, search all child nodes
	if(top_left_child != nullptr)
	{
		// add the count from each quad in case search area is over multiple quads.
		count += top_left_child->search(search_area);
		count += top_right_child->search(search_area);
		count += bottom_left_child->search(search_area);
		count += bottom_right_child->search(search_area);
		return count;
	}
	
	// only executes if the current quad is a leaf node,
	// which will return number of entities in collision region.
	return entities.size();
}

bool QuadTree::collisions(sf::FloatRect search_area)
{
	// bools to check if there have been collisions from the child nodes.
	bool collision_top_left = false;
	bool collision_top_right = false;
	bool collision_btm_left = false; 
	bool collision_btm_right = false;

	sf::FloatRect entity_rect = sf::FloatRect(0, 0, 0, 0);

	// check that the search area is in the current quad
	if(!boundry.intersects(search_area))
	{
		// if not in the current quad, return false.
		return false;
	}

	// check that the tree has child nodes
	if(top_left_child != nullptr)
	{
		// if node has children, check there collisions
		collision_top_left = top_left_child->collisions(search_area);
		collision_top_right = top_right_child->collisions(search_area);
		collision_btm_left = bottom_left_child->collisions(search_area);
		collision_btm_right = bottom_right_child->collisions(search_area);

		// OR them all together, as if one or more are true, then there has been  a collision.
		return (collision_top_left || collision_top_right) || (collision_btm_left || collision_btm_right);
	}

	// if we are in the leaf nodes, loop through the nodes that are referenced in this quad.
	for(Point *s : entities)
	{
		// return true only if there is a collision with one of this points
		entity_rect = s->getGlobalBounds();
		if(search_area.intersects(entity_rect))
		{
			return true;
		}
	}

	// Otherwise return false if there are no collisions.
	return false;
}

void QuadTree::clear()
{
	// Delete each of the child nodes in the tree if they are not null.
	// Once deleted, set the pointer to be a null pointer.
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
	entities.clear();
}

bool QuadTree::insert(Point *shape)
{
	// get the global bounds to check that the shape is in
	// this region of the world space.
	sf::FloatRect shape_rect = shape->getGlobalBounds();
	
	// Check that the current shape is in this part of the tree.
	if(!boundry.intersects(shape_rect))
	{
		// If the shape does not intersect, then return false as
		// it is not in this part of the tree.
		return false;
	}

	// if the quad tree has not exceeded its child threshold
	// and is a leaf node, then add it to the list of entities.
	if(entities.size() < CHILD_THRRESHOLD && top_left_child == nullptr)
	{
		entities.emplace_back(shape);
		return true;
	}

	// If threshold has been exceeded as a leaft node,
	// then we subdivide the current quad.
	if(top_left_child == nullptr)
	{
		subdivide();
	}
	
	// attempt to insert the current shape into one of the child quads.
	if(top_left_child->insert(shape)) { return true; }
	
	if(top_right_child->insert(shape)) { return true; }
	
	if(bottom_left_child->insert(shape)) { return true; }
	
	if(bottom_right_child->insert(shape)) { return true; }

	// Should never be able to reach this statement,
	// but return false if by some chance it occurs.
	return false;
}


int QuadTree::maxDepth() const
{
	int i = 0;

	// set largest to be the current depth as if the quad has children,
	// then the depth can only get larger.
	int largest = depth;

	// depths array to store the depth for each child
	// DEPTH_ARRAY_SIZE is set to 4, as tree has 4 child nodes.
	int depths[DEPTH_ARRAY_SIZE] = {0, 0, 0, 0};

	// if this quad is not a leaf node, get the depth from each child node.
	if(top_left_child != nullptr)
	{
		depths[0] = top_left_child->maxDepth();
		depths[1] = top_right_child->maxDepth();
		depths[2] = bottom_left_child->maxDepth();
		depths[3] = bottom_right_child->maxDepth();
	}
	
	// loop through array and check that current
	// depth is not smaller than those from the child branches.
	for(i = 0; i < DEPTH_ARRAY_SIZE; ++i)
	{
		// if the largest is less than the current depth, make the depth the new largest.
		if(largest < depths[i])
		{
			largest = depths[i];
		}
	}
	return largest;
}

PointVector * QuadTree::retrieve(PointVector * returnList, sf::FloatRect search)
{
	if(!boundry.intersects(search))
	{
		return returnList;
	}

	if(top_left_child != nullptr)
	{
		top_left_child->retrieve(returnList, search);
		top_right_child->retrieve(returnList, search);
		bottom_left_child->retrieve(returnList, search);
		bottom_right_child->retrieve(returnList, search);

		return returnList;
	}

	if(entities.size() == 0)
	{
		return returnList;
	}

	for(Point *p : entities)
	{
		if(p->getGlobalBounds() == search)
		{
			continue;
		}
		returnList->push_back(p);
	}
	return returnList;
}

void QuadTree::display(sf::RectangleShape *shape, sf::RenderWindow *target)
{
	// set the quad size and position.
	shape->setSize(sf::Vector2f(boundry.width, boundry.height));
	shape->setPosition(boundry.left, boundry.top);
	
	// draw the square
	target->draw(*shape);

	// if not a leaf node, recursively go down each child to draw the entire quad tree.
	if(top_left_child != nullptr)
	{
		top_left_child->display(shape, target);
		top_right_child->display(shape, target);
		bottom_left_child->display(shape, target);
		bottom_right_child->display(shape, target);
	}
}

void QuadTree::subdivide()
{
	// increase the current depth by 1 for the children nodes
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
