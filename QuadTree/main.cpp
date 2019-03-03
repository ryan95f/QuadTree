#include <SFML\Graphics.hpp>
#include "QuadTree.hpp"

int main()
{

	sf::RenderWindow window(sf::VideoMode(500, 500), "Hello World");
	QuadTree tree(sf::FloatRect(0, 0, 500, 500));

	sf::CircleShape circle1(5);
	sf::CircleShape circle2(5);
	sf::CircleShape circle3(5);
	sf::CircleShape circle4(5);
	sf::CircleShape circle5(5);
	circle1.setPosition(250, 220);
	circle2.setPosition(100, 50);
	circle3.setPosition(400, 400);
	circle4.setPosition(10, 20);
	circle5.setPosition(10, 50);

	tree.insert(&circle1);
	tree.insert(&circle2);
	tree.insert(&circle3);
	tree.insert(&circle4);
	tree.insert(&circle5);

	
	// set up the display square
	sf::RectangleShape s;
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(1);

	while(window.isOpen())
	{
		sf::Event evnt;
		while(window.pollEvent(evnt))
		{
			if(evnt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		tree.display(&s, &window);

		window.draw(circle1);
		window.draw(circle2);
		window.draw(circle3);
		window.draw(circle4);
		window.draw(circle5);

		window.display();
	}
	return 0;
}