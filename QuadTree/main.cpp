#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "QuadTree.hpp"

#define POINT_WIDTH 5
#define N_SQUARES 14
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
	float x = 0;
	float y = 0;

	// Set the random seed
	// srand((unsigned int) time(NULL));
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quad Tree");
	
	// Create the quad tree
	QuadTree tree(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	// create and insert the circles into the quad tree
	sf::RectangleShape squares[N_SQUARES];
	for(int i = 0; i < N_SQUARES; ++i)
	{
		x = (float) (rand() % WINDOW_WIDTH);
		y = (float) (rand() % WINDOW_HEIGHT);
		squares[i].setSize(sf::Vector2f(POINT_WIDTH, POINT_WIDTH));
		squares[i].setPosition(x, y);
		squares[i].setOrigin(POINT_WIDTH / 2.0f, POINT_WIDTH / 2.0f);
		tree.insert(&squares[i]);
	}
	
	 //sf::RectangleShape m(sf::Vector2f(30, 30));
	 //m.setPosition(250, 300);

	// set up the display square
	sf::RectangleShape s;
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(1);

	std::cout << "Max Depth: " << tree.maxDepth() << std::endl;


	while(window.isOpen())
	{
		sf::Event evnt;
		while(window.pollEvent(evnt))
		{
			if(evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			/*else if(evnt.type == sf::Event::MouseButtonReleased)
			{
				float x = (float) evnt.mouseButton.x;
				float y = (float) evnt.mouseButton.y;
				m.setPosition(x, y);
				bool a = tree.collisions(m.getGlobalBounds());
				std::cout << a << std::endl;
			}*/
		}

		window.clear(sf::Color::Black);

		// Draw the tree
		tree.display(&s, &window);

		// Draw the squares that are within the tree
		for(int i = 0; i < N_SQUARES; ++i)
		{
			window.draw(squares[i]);
		}

		 //window.draw(m);

		// Display drawn objects
		window.display();
	}
	return 0;
}