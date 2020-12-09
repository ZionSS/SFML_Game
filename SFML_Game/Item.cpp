#include "Item.h"

Item::Item(sf::Texture* texture)
{
	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setPosition(position);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Item::~Item()
{
}

void Item::Update(float deltaTime, sf::Vector2f position)
{
	body.setPosition(position);
}

void Item::Draw(sf::RenderWindow& window)
{
		window.draw(body);
}
