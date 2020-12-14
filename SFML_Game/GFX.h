#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class GFX
{
public:
	GFX(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~GFX();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	bool faceRight;
};

