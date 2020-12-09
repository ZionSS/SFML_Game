#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Item
{
public:
	Item(sf::Texture* texture);
	~Item();
	void Update(float deltaTime, sf::Vector2f position);
	Collider GetCollider() { return Collider(body); }
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	sf::Vector2f position;
	
};

