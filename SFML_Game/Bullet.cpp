#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
	: animation(texture,imageCount,switchTime)
{
	this->dmg = 50;
	this->speed = speed;
	maxSpeed = 10.0f;
	shape.setSize(sf::Vector2f(10.0f, 10.0f));
	shape.setOrigin(shape.getSize() / 2.0f);
	shape.setTexture(texture);
}
Bullet::~Bullet() {};

void Bullet::Update(float deltaTime, sf::Vector2f position, sf::Vector2f size, sf::Vector2i getMousePosition )
{
	playerCenter = sf::Vector2f(position.x,position.y);
	shape.setPosition(playerCenter);
	shape.setSize(size);
	shape.setOrigin(shape.getSize() / 2.0f);
	mousePosition = sf::Vector2f(getMousePosition);
	aimDirection = mousePosition - playerCenter;
	aimDirectionNormalize = aimDirection / sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2));
	curveVelocity = aimDirectionNormalize * maxSpeed;
	animation.Update(0, deltaTime, 0);
	shape.setTextureRect(animation.uvRect);
}

void Bullet::getMove()
{
	 shape.move(curveVelocity);
}
void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}