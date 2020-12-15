#include "Menu.h"



Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("upheavtt.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(52);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play");
	menu[0].setOrigin(0, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width * 1 / 10,( height *6/10)));

	menu[1].setFont(font);
	menu[1].setCharacterSize(52);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(0, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width * 1 / 10, height * 7 / 10));

	menu[2].setFont(font);
	menu[2].setCharacterSize(52);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("How to play");
	menu[2].setOrigin(0, menu[1].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width * 1 / 10, height * 8 / 10));

	menu[3].setFont(font);
	menu[3].setCharacterSize(52);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setOrigin(0, menu[2].getLocalBounds().height / 2);
	menu[3].setPosition(sf::Vector2f(width *1/10, height *9/10));



}

Menu::~Menu()
{

}

void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::getItem(sf::Vector2f mousePosition)
{
	this->selectedItem = 9;
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (menu[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)))
		{
			menu[i].setFillColor(sf::Color::Red);
			this->selectedItem = i;
		}
		else
		{
			menu[i].setFillColor(sf::Color::White);
		}
		
	}
}

