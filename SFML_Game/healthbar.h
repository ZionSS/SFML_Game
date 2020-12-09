#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class healthbar
{
public:
	healthbar(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float hp);
	~healthbar();
	void Update(float deltaTime,float hp,sf::Vector2f position);
	void setHealth(bool state);
	int getHitCount() { return hitCount; }
	void Draw(sf::RenderWindow& window);
private:
	sf::Vector2f position;
	float maxHealth;
	float hp;
	sf::RectangleShape body;
	unsigned int row;
	Animation animation;
	unsigned int hitCount;
	bool healthState;
};

