#include "Button.h"

Button::Button(sf::Font* font, int size, float width, float height)
{
	text[0].setFont(*font);
	text[0].setCharacterSize(size);
	text[0].setFillColor(sf::Color::White);
	text[0].setString("Continue");
	text[0].setOrigin(sf::Vector2f(text[0].getLocalBounds().width / 2, text[0].getLocalBounds().height / 2));
	text[0].setPosition(width/2,height*3/7);
	
	text[1].setFont(*font);
	text[1].setCharacterSize(size);
	text[1].setFillColor(sf::Color::White);
	text[1].setString("Exit");
	text[1].setOrigin(sf::Vector2f(text[1].getLocalBounds().width / 2, text[1].getLocalBounds().height / 2));
	text[1].setPosition(width / 2, (height * 3 / 7)+size);
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& window)
{
	for(int i =0 ;i<2;i++)
	window.draw(text[i]);
}

void Button::Update(sf::Vector2f mousePosition)
{
	this->selectItem = 9;
	for(int i =0;i<2;i++)
	{
		if (text[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		{
			text[i].setFillColor(sf::Color::Red);
			this->selectItem = i;
		}
		else
		{
			text[i].setFillColor(sf::Color::White);
		}
	}
	
}
