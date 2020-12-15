#include "Enemy.h" 

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed ): 
	animation(texture, imageCount, switchTime) {
	this->hp = 150;
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setPosition(position);
	body.setSize(sf::Vector2f(37.875f,38.0f));
	hitbox.setPosition(position);
	hitbox.setSize(sf::Vector2f(17.875f, 18.0f));
	hitbox.setOrigin(hitbox.getSize() / 2.0f);
	body.setOrigin(body.getSize() / 2.0f);
	hitbox.setFillColor(sf::Color::Transparent);
	body.setTexture(texture);

}

Enemy::~Enemy() {}

void Enemy::setHp(float dmg)
{
	this->hp -= dmg;
}

void Enemy::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
	hitbox.setPosition(position);
}

void Enemy::enemyUpdate(float deltaTime, sf::Vector2f playerPosition)
{
	faceRight = true;
	sf::Vector2f enemyMove;
	if ((abs(playerPosition.y - body.getPosition().y) > abs(playerPosition.x - body.getPosition().x))&& body.getPosition().y < playerPosition.y)
	{
		row = 0;
	}
	if ((abs(playerPosition.y - body.getPosition().y) > abs(playerPosition.x - body.getPosition().x)) && body.getPosition().y > playerPosition.y)
	{
		row = 1;
	}
	if ((abs(playerPosition.x - body.getPosition().x) > abs(playerPosition.y - body.getPosition().y))&& body.getPosition().x < playerPosition.x)
	{
		row = 2;
	}
	if ((abs(playerPosition.x - body.getPosition().x) > abs(playerPosition.y - body.getPosition().y)) && body.getPosition().x > playerPosition.x)
	{
		row = 2;
		faceRight = false;
	}
	moveDirection = playerPosition - body.getPosition();
	moveDirectionNorm = moveDirection/sqrt(pow(moveDirection.x, 2) + pow(moveDirection.y, 2));
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(moveDirectionNorm*speed);
	hitbox.move(moveDirectionNorm*speed);

}
void Enemy::Draw(sf::RenderWindow &window)
{
	window.draw(body);
	window.draw(hitbox);
}

void Enemy::getDifficult(float difficult)
{
	if (difficult / 60> rate)
	{
		rate++;
	}
	hp = 150 * rate * 0.5;
	
		speed = 0.25 * rate;
	if(speed>2)
		speed = 1.75;

}
