#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Math.h"
#include "Collider.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();
	void setHp(float dmg);
	void setPosition(sf::Vector2f position);
	float getHp() { return hp; }
	float getDmg() { return dmg; }
	void Draw(sf::RenderWindow &window);
	void enemyUpdate(float deltaTime,sf::Vector2f playerPosition);
	sf::Vector2f GetPosition() { return	body.getPosition(); }
	Collider GetCollider() { return Collider(hitbox); }
private:
	unsigned int row;
	float hp;
	sf::RectangleShape body;
	sf::RectangleShape hitbox;
	float speed;
	Animation animation;
	bool faceRight;
	float dmg;
	sf::Vector2f position;
	sf::Vector2f moveDirection;
	sf::Vector2f moveDirectionNorm;
};
