#ifndef __POINT_HPP
#define __POINT_HPP

#include <SFML\Graphics.hpp>

#define POINT_WIDTH 5
#define POINT_HEIGHT 5
#define POINT_X_VELOCITY 0.4f
#define POINT_Y_VELOCITY 0.4f

struct Point
{
	sf::Vector2f pos;
	sf::Vector2f increment;

	Point()
	{
		pos = sf::Vector2f(0, 0);
		increment = sf::Vector2f(POINT_X_VELOCITY, POINT_Y_VELOCITY);
	}

	sf::FloatRect getGlobalBounds() const
	{
		return sf::FloatRect(pos.x, pos.y, POINT_WIDTH, POINT_HEIGHT);
	}
};


#endif // __POINT_HPP