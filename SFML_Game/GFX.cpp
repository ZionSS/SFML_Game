#include "GFX.h"

GFX::GFX(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 0;

	body.setSize(sf::Vector2f(96.0f, 256.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

GFX::~GFX()
{
}

void GFX::Update(float deltaTime)
{
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void GFX::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
