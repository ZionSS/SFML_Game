#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	Button( sf::Font *font, int size,float width,float height);
	~Button();
	void Draw(sf::RenderWindow& window);
	void Update(sf::Vector2f mousePosition);
	bool getSelect() { return selectItem; }

private:
	sf::Text text[2];
	int selectItem=0;
};

