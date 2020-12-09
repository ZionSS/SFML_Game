
#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,sf::RenderWindow& window ) :
	animation(texture, imageCount, switchTime)
{
	this->hp = 20.0f;
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(30.0f, 38.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f,206.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::setHp(float dmg)
{
	this->hp -= dmg;
}

void Player::reHp()
{
	this->hp = 20.0f;
}

void Player::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.0f;
	velocity.y *= 0.0f;
	if (row == 1) {
		row = 0;
	}
	if (row == 3) {
		row = 2;
	}
	if (row == 5) {
		row = 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
		row = 3;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
		row = 3;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= speed;
		row = 5;
		if (velocity.y > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += speed;
		row = 1;
		if (velocity.y > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
}

