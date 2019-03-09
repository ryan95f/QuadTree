#ifndef __POINT_HPP
#define __POINT_HPP

#include <SFML\Graphics.hpp>

#define POINT_WIDTH 5
#define POINT_HEIGHT 5

enum class Horizontal
{
	LEFT = 0,
	RIGHT,
};

enum class Vertical
{
	UP = 0,
	DOWN
};

struct Point
{
	sf::Vector2f pos;
	Horizontal horizontal;
	Vertical vertical;

	sf::FloatRect getGlobalBounds() const
	{
		return sf::FloatRect(pos.x, pos.y, POINT_WIDTH, POINT_HEIGHT);
	}
};


#endif // __POINT_HPP