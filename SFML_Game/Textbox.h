#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
class Textbox
{
public:
	
	Textbox(int size, sf::Color color, bool sel);
	~Textbox();
	
	
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f position);
	void setLimit(bool ToF,int isLimit);
	void setSelected(bool sel);
	std::string getText() { return text.str(); }
	void drawTo(sf::RenderWindow& window);
	void typeOn(sf::Event input);
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;

	void inputLogic(int charTyped);

	void deleteLastChar();
};

