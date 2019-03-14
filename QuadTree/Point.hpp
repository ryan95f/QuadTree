#ifndef __POINT_HPP
#define __POINT_HPP

#include <SFML\Graphics.hpp>

#define POINT_WIDTH 5
#define POINT_HEIGHT 5
#define POINT_X_VELOCITY 0.4f
#define POINT_Y_VELOCITY 0.4f
#define DEFAULT_COLOUR sf::Color::White;
#define COLLISION_INDICATOR_DURATION 50

struct Point
{
	sf::Vector2f pos;
	sf::Vector2f increment;
	sf::Color colour;
	int indicator_duration;

	Point()
	{
		indicator_duration = 0;
		pos = sf::Vector2f(0, 0);
		increment = sf::Vector2f(POINT_X_VELOCITY, POINT_Y_VELOCITY);
		colour = DEFAULT_COLOUR;
	}

	void update(float dt)
	{
		if(indicator_duration < COLLISION_INDICATOR_DURATION)
		{
			++indicator_duration;
		}
		else
		{
			indicator_duration = 0;
			colour = DEFAULT_COLOUR;
		}
	}

	sf::FloatRect getGlobalBounds() const
	{
		return sf::FloatRect(pos.x, pos.y, POINT_WIDTH, POINT_HEIGHT);
	}
	
	void resolveCollision()
	{
		indicator_duration = 0;
		increment.x = -increment.x;
		increment.y = -increment.y;
		colour = sf::Color::Red;
		
	}
};


#endif // __POINT_HPP