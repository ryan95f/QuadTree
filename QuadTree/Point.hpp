#ifndef __POINT_HPP
#define __POINT_HPP

#include <SFML\Graphics.hpp>

#define POINT_WIDTH 5
#define POINT_HEIGHT 5
#define POINT_X_VELOCITY 0.4f
#define POINT_Y_VELOCITY 0.4f
#define DEFAULT_COLOUR sf::Color::White;
#define COLLISION_INDICATOR_DURATION 50

/**
 * Point represents a single square within a game.
 */
struct Point
{
	sf::Vector2f pos;
	sf::Vector2f increment;
	sf::Color colour;
	int indicator_duration;

	/**
	 * Point Constructor
	 */
	Point()
	{
		// set up instance variables
		indicator_duration = 0;
		pos = sf::Vector2f(0, 0);
		increment = sf::Vector2f(POINT_X_VELOCITY, POINT_Y_VELOCITY);
		colour = DEFAULT_COLOUR;
	}

	/**
	 * Update the point during each "tick" within the game.
	 * This will alter the movement of the point
	 * @param dt - Delta Time step that the game is running at.
	 */
	void update(float dt)
	{
		if(indicator_duration < COLLISION_INDICATOR_DURATION)
		{
			// update the duratin length
			++indicator_duration;
		}
		else
		{
			// reset the colour back to default once the duration has exceeded its limit. 
			indicator_duration = 0;
			colour = DEFAULT_COLOUR;
		}
	}

	/**
	 * Gets the boundry of the point within the world space.
	 */
	sf::FloatRect getGlobalBounds() const
	{
		return sf::FloatRect(pos.x, pos.y, POINT_WIDTH, POINT_HEIGHT);
	}
	
	/**
	 * Method that is executed each time the object has had a collision.
	 */
	void resolveCollision()
	{
		indicator_duration = 0;

		// adjust the movement of the point to be in the opposite direction.
		increment.x = -increment.x;
		increment.y = -increment.y;

		// change colour to red to indicate its has had a collision.
		colour = sf::Color::Red;
	}
};

#endif // __POINT_HPP