#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Math.h"
class Bullet
{
public:
	Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
		~Bullet();
	void Update(float deltaTime,sf::Vector2f position, sf::Vector2f size,sf::Vector2i mousePostion);
	void getMove();
	float getDmg() { return dmg; }
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return	shape.getPosition(); }
	Collider GetCollider() { return Collider(shape); }

private:
	sf::Vector2f mousePosition;
	sf::Vector2f playerCenter;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalize;
	sf::Vector2f curveVelocity;
	Animation animation;
	float delay;
	float dmg;
	float timeCount;
	sf::RectangleShape shape;
	float speed;
	float maxSpeed;
};

