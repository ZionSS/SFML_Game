#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed, sf::RenderWindow& window);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() {return	body.getPosition();}
	float getHp() { return hp; }
	void setHp(float dmg);
	void reHp();
	void setPosition(sf::Vector2f position);
	Collider GetCollider() { return Collider(body); }
							
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	float hp;
	sf::Vector2f velocity;

};

