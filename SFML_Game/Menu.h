#pragma once
#include <SFML/Graphics.hpp>
#define MAX_ITEMS 4
class Menu
{
public:
	Menu(float width,float height);
	~Menu();

	void Draw(sf::RenderWindow& window);
	void getItem(sf::Vector2f mousePosition);
	int getState() { return selectedItem; }
	
private:
	int selectedItem=9;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];
};

