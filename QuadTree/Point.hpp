#ifndef __POINT_HPP
#define __POINT_HPP

#include <SFML\Graphics.hpp>

#define POINT_WIDTH 5
#define POINT_HEIGHT 5

enum class Direction { LEFT, RIGHT };

struct Point
{
	Direction direction;
	sf::Vector2f pos;
	sf::Vector2f increment;

	Point()
	{
		pos = sf::Vector2f(0, 0);
		direction = Direction::LEFT;
		increment = sf::Vector2f(0.4f, 0.4f);
	}

	sf::FloatRect getGlobalBounds() const
	{
		return sf::FloatRect(pos.x, pos.y, POINT_WIDTH, POINT_HEIGHT);
	}
};


#endif // __POINT_HPP