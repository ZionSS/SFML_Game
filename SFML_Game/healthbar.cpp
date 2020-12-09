#include "healthbar.h"

healthbar::healthbar(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float hp) :
	animation(texture,imageCount,switchTime)
{
	hitCount = 3;
	body.setSize(sf::Vector2f(40.0f , 32.5f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(sf::Vector2f(32.0f, 32.0f));
	body.setTexture(texture);
	row = 0;
}

healthbar::~healthbar()
{
}

void healthbar::Update(float deltaTime, float hp, sf::Vector2f position)
{
	if (hitCount == 2)
	{
		row = 0;
	}
	else if (hitCount == 1)
	{
		row = 1;
	}
	else if (hitCount == 0)
	{
		row = 2;
	}
	body.setPosition(position);
	animation.Update(row, deltaTime,1);
	body.setTextureRect(animation.uvRect);
}

void healthbar::setHealth(bool state)
{
	if (state)
	{
		if (hitCount != 2)
			hitCount += 1;
	}
	else
	{
		if (hitCount != 0)
			hitCount -= 1;
	}
}

void healthbar::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


