#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Player.h"
#include "Platform.h"

static const float View_HEIGHT = 720.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)* aspectRatio, View_HEIGHT );
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Howling Abyss");
	sf::RectangleShape wall(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 1000.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_HEIGHT, View_HEIGHT));
	
	sf::Texture isacTexture;
	sf::Texture isacHead;
	isacTexture.loadFromFile("Isaac_Body02.png");
	isacHead.loadFromFile("Isaac_Head02.png");
	Player playerBody(&isacTexture, sf::Vector2u(9,4 ), 0.1f, 100.0f);
	PlayerHead playerHead(&isacHead, sf::Vector2u(1,8), 0.0f, 100.0f);
	

	float deltaTime = 0.0f;
	sf::Clock clock;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
					ResizeView(window, view);
					break;
			}
		}
		
		playerBody.Update(deltaTime);
		playerHead.Update1(deltaTime);
		

		Collider monsterCollision = playerBody.GetCollider(); // Dammit!!!!
		sf::Vector2f direction;
		
		window.clear(sf::Color(150,150,150));
		window.draw(wall);
		window.setView(view);
		playerBody.Draw(window);
		playerHead.Draw1(window);
		
		window.display();
	}
	return 0;
}
