
#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 0.0f);
	body.setTexture(texture);
}
PlayerHead::PlayerHead(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(64.0f, 64.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, -22.5f);
	body.setTexture(texture);
}
Player::~Player()
{
}
PlayerHead::~PlayerHead()
{
}

void PlayerHead::Update1(float deltaTime)
{
	
	velocity.x *= 0.0f;
	velocity.y *= 0.0f;
	if (row == 6) {
		row = 2;
	}
	if (row == 4) {
		row = 0;
	}
	if (row == 5) {
		row = 1;
	}
	if (row == 7) {
		row = 3;
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			velocity.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			velocity.y += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			row = 6;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			row = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			row = 7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			row = 4;
		}

		
	animation.Update(row, deltaTime,faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
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
		row = 1;
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
void PlayerHead::Draw1(sf::RenderWindow& window)
{
	window.draw(body);
}
