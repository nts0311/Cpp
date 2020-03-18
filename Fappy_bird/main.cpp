#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "Bird.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;
using namespace sf;



/*int main()
{
	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand(); // get rid of first result
	rand();

	sf::RenderWindow window(sf::VideoMode(288, 512), "Fappy Bird");

	float deltaTime(0.0f);
	Clock clock1;

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	Sprite p;
	Texture pt;
	pt.loadFromFile("sprites//pipe-green.png");

	p.setTexture(pt);
	p.setPosition(288 / 2, 0);

	Game g(window);

	while (window.isOpen())
	{
		deltaTime = clock1.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				//b.flyUp();
			}
		}
		//Animations go here
		//b.updateAnimation(deltaTime);

		while (accumulator > ups)
		{
			accumulator -= ups;
			//UpdateLogic();
			//AI();
			//Physics();
			//b.fallDown();
			//pi.moveLeft();
		}



		window.clear();
		//draw here
		g.draw();
		window.display();
		accumulator += clock.restart();

	}

	return 0;
}*/

int main()
{
	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand(); // get rid of first result
	rand();
	sf::RenderWindow window(sf::VideoMode(288, 512), "Fappy Bird");

	float deltaTime(0.0f);
	Clock clock1;

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);


	Game g(window);


	while (window.isOpen())
	{
		deltaTime = clock1.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (g.isOver())
					g.reset();
				else
				{
					g.getBird().flyUp();
					g.playWingSound();
				}
			}

			if (event.type == Event::KeyPressed)
			{
				if (g.isOver())
					g.reset();
				else
				{
					g.getBird().flyUp();
					g.playWingSound();
				}
			}
				
		}
		//Animations go here
		g.updateAnimation(deltaTime);

		while (accumulator > ups)
		{
			accumulator -= ups;
			//UpdateLogic();
			//AI();
			//Physics();
			//b.fallDown();
			//b.move();
			g.update();
		}



		window.clear();
		//draw here
		g.draw();

		window.display();
		accumulator += clock.restart();
	
		Sleep(1);
	}

	return 0;
}

