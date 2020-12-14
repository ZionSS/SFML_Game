#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include"Player.h"
#include"Menu.h"
#include "Platform.h"
#include "Enemy.h"
#include "GFX.h"
#include "Bullet.h"
#include "healthbar.h"
#include "Item.h"
#include "Textbox.h"
bool randomItemSpwanRate(int dropRate);
void showHighScore(int x, int y, std::string word, sf::RenderWindow& window, sf::Font* font);

static const float View_HEIGHT = 720.0f;
sf::Vector2f viewSize(936, 624);
sf::VideoMode vm(viewSize.x, viewSize.y);

std::vector<std::vector<int>> tiles;
sf::RectangleShape wall;
std::vector<Platform> walls;
void setTiles()
{
	tiles = {
		//////0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//0
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//0
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//0
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//3
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//4
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//5
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//6
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//7
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//8
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//9
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//03
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//04
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//05
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//06
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//07
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//08
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//09
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//00
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}//03

	};
}
void setWalls()
{
	for (int x = 0; x < 39; x++)
	{
		for (int y = 0; y < 26; y++)
		{
			if (tiles[y][x] == 1)
			{
				Platform temp(nullptr, sf::Vector2f(24.0f, 24.0f),sf::Vector2f(((x) * 24.0f), ((y) * 24.0f)));
				
				walls.push_back(temp);
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(936, 624), "Howling Abyss", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);
	srand(time(NULL));
	sf::Font font;
	font.loadFromFile("upheavtt.ttf");

	FILE* scoreFile;
	char playerName[255];
	int playerScore[6];
	std::string name[6];
	std::vector <std::pair<int, std::string>> userScore;

	playerScore[5] = -99;
	name[5] = "-";

	scoreFile = fopen("Score.txt","r");
	for(int i =0;i<5;i++)
	{
		fscanf(scoreFile, "%s", &playerName);
		name[i] = playerName;
		fscanf(scoreFile, "%d", &playerScore[i]);
		userScore.push_back(make_pair(playerScore[i], name[i]));
	}
	userScore.push_back(make_pair(playerScore[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(scoreFile);

	fopen("Score.txt", "w");
	for (size_t i = 5; i >= 1; i--)
	{
		strcpy(playerName, userScore[i].second.c_str());
		fprintf(scoreFile, "%s %d\n", playerName, userScore[i].first);
	}
	fclose(scoreFile);

	sf::RectangleShape mouseCursor;
	sf::Vector2f playerCenter;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalize;
	sf::Vector2f itemLocate;
	sf::Texture map;
	sf::Texture tearIsaac;
	sf::Texture enemy01;
	sf::Texture hpbar;
	sf::Texture menuBG;
	sf::Texture lightFX;
	sf::Texture pic;
	sf::Texture lost;
	sf::Texture isacTexture;
	isacTexture.loadFromFile("./Resource/Player/IsaacPlayer.png");
	map.loadFromFile("./Resource/Map/Map01.png");
	lost.loadFromFile("./Resource/gfx/playerportraitbig_12_thelost.png");
	pic.loadFromFile("./Resource/gfx/playerportraitbig_01_isaac.png");
	lightFX.loadFromFile("./Resource/gfx/the_marshall_light.png");
	menuBG.loadFromFile("./Resource/Map/MenuBG.jpg");
	hpbar.loadFromFile("./Resource/Item/hearts.png");
	enemy01.loadFromFile("./Resource/Enemy/Wizob.png");
	tearIsaac.loadFromFile("./Resource/Tear/Tear0.png");
	//Item//
	sf::Texture item01;
	sf::Texture item02;
	sf::Texture item03;
	sf::Texture item04;
	sf::Texture item05;
	sf::Texture item06;
	sf::Texture item07;
	sf::Texture item08;
	sf::Texture item09;
	sf::Texture item10;
	sf::Texture item11;
	sf::Texture item12;

	item01.loadFromFile("./Resource/Item/Attack_Speed.png");
	item02.loadFromFile("./Resource/Item/Damage.png");
	item03.loadFromFile("./Resource/Item/Health_Boost.png");
	item04.loadFromFile("./Resource/Item/Health_Drop.png");
	item05.loadFromFile("./Resource/Item/Random.png");
	item06.loadFromFile("./Resource/Item/Rewind.png");
	item07.loadFromFile("./Resource/Item/Score_plus.png");
	item08.loadFromFile("./Resource/Item/Score.png");
	item09.loadFromFile("./Resource/Item/Shield.png");
	item10.loadFromFile("./Resource/Item/Super_Score_Boost.png");
	item11.loadFromFile("./Resource/Item/Tear_Size.png");
	item12.loadFromFile("./Resource/Item/Zawarudo.png");

	Item AS(&item01);
	Item Dmg(&item02);
	Item HB(&item03);
	Item HD(&item04);
	Item Ran(&item05);
	Item RW(&item06);
	Item SP(&item07);
	Item SC(&item08);
	Item SH(&item09);
	Item SSB(&item10);
	Item TS(&item11);
	Item ZW(&item12);

	std::vector<Item> ASitem;
	ASitem.push_back(Item(AS));
	std::vector<Item> Dmgitem;
	Dmgitem.push_back(Item(Dmg));
	std::vector<Item> HBitem;
	HBitem.push_back(Item(HB));
	std::vector<Item> HDitem;
	HDitem.push_back(Item(HD));
	std::vector<Item> Ranitem;
	Ranitem.push_back(Item(Ran));
	std::vector<Item> RWitem;
	RWitem.push_back(Item(RW));
	std::vector<Item> SPitem;
	SPitem.push_back(Item(SP));
	std::vector<Item> SCitem;
	SCitem.push_back(Item(SC));
	std::vector<Item> SHitem;
	SHitem.push_back(Item(SH));
	std::vector<Item> SSBitem;
	SSBitem.push_back(Item(SSB));
	std::vector<Item> TSitem;
	TSitem.push_back(Item(TS));
	std::vector<Item> ZWitem;
	ZWitem.push_back(Item(ZW));
	///////////////////////
	sf::RectangleShape theLost(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape xiaO(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape menuBackground(sf::Vector2f(936, 624));
	sf::RectangleShape lightfx(sf::Vector2f(96*1.5, 256*1.5));
	sf::RectangleShape map01(sf::Vector2f(936, 624));
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 1000.0f));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_HEIGHT, View_HEIGHT));

	Bullet tear(&tearIsaac, sf::Vector2u(1, 1), 3.0f, 100.0f);
	Enemy Wizob(&enemy01, sf::Vector2u(4, 3), 0.25f, 0.5f);
	healthbar health(&hpbar, sf::Vector2u(1, 3), 3.0f, 200.0f);
	Menu menu(window.getSize().x, window.getSize().y);
	Player playerBody(&isacTexture, sf::Vector2u(9, 6), 0.1f, 100.0f, window);
	Textbox nameInput(15, sf::Color::White, false);

	std::vector<Bullet> bullets;
	std::vector<Enemy> wizobGroub;
	std::vector<healthbar> HP;

	bullets.push_back(Bullet(tear));
	wizobGroub.push_back(Enemy(Wizob));
	for (int i = 0; i < 3; i++)
		HP.push_back(healthbar(health));

	theLost.setTexture(&lost);
	xiaO.setTexture(&pic);
	menuBackground.setTexture(&menuBG);
	lightfx.setTexture(&lightFX);
	map01.setTexture(&map);

	wall.setFillColor(sf::Color::Red);
	wall.setSize(sf::Vector2f(24.0f, 24.0f));
	setTiles();
	setWalls();

	nameInput.setFont(font);
	nameInput.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
	nameInput.setLimit(true, 10);

	Collider isaacBodyCollision = playerBody.GetCollider(); // Dammit!!!!
	Collider wizobCollider = Wizob.GetCollider();
	Collider asItemCollider = AS.GetCollider();
	Collider bulletColiider = tear.GetCollider();

	sf::Clock clock;
	sf::Clock shootClock;
	sf::Clock wizobSpawnCounter;
	sf::Clock dmgCheck;
	
	int gameState = 0;
	bool checkDmg = false;
	int score = 0;
	float spawnTime;
	float shootDelay = 0.0f;
	float deltaTime = 0.0f;
	float attackSpeed = 1.0f;
	int k = HP.size() - 1;
	int timing;
	int itemCount01 = ASitem.size() - 1;
	int itemCount02 = Dmgitem.size() - 1;
	int itemCount03 = HBitem.size() - 1;
	int itemCount05 = Ranitem.size() - 1;
	int itemCount07 = SPitem.size() - 1;
	int itemCount08 = SCitem.size() - 1;
	int itemCount09 = SHitem.size() - 1;
	int itemCount10 = SSBitem.size() - 1;
	int dropRate = 2;
	itemCount01++;
	itemCount02++;
	itemCount03++;
	itemCount05++;
	itemCount07++;
	itemCount08++;
	itemCount09++;
	itemCount10++;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::TextEntered:
				nameInput.typeOn(event);
				break;
			}
		}
		if (gameState == 0)
		{
			menu.getItem(sf::Vector2f(sf::Mouse::getPosition(window)));
			if (menu.getState() == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameState = 1;
			}
			else if (menu.getState() == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameState = 3;
			}
			else if (menu.getState() == 2 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.close();
			}
			lightfx.setPosition(sf::Vector2f(85.0f, 0.0f));
			xiaO.setPosition(sf::Vector2f(110.0f, 235.0f));
			theLost.setPosition(sf::Vector2f(110.0f, 205.0f));
			window.clear();
			window.draw(menuBackground);
			if(rand()%50!=0&& menu.getState() != 0)
			{ 
				
				window.draw(xiaO);
				window.draw(lightfx);
			}
			if (menu.getState() == 0)
			{
				if (rand() % 10 != 0)
				{
					window.draw(theLost);
					window.draw(lightfx);
				}
				
			}
			menu.Draw(window);
			window.display();
		}
		if (gameState == 1)
		{
			nameInput.setSelected(true);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				nameInput.setSelected(false);
				gameState = 2;
			}
			window.clear();
			window.draw(menuBackground);
			nameInput.drawTo(window);
			window.display();
		}
		if (gameState == 2)
		{
			deltaTime = clock.restart().asSeconds();
			shootDelay = shootClock.getElapsedTime().asSeconds();
			spawnTime = wizobSpawnCounter.getElapsedTime().asSeconds();
			timing = dmgCheck.getElapsedTime().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
		//std::cout << shootDelay<< std::endl;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootDelay > attackSpeed)
			{
				bullets.push_back(Bullet(tear));
				shootDelay = shootClock.restart().asSeconds();
			}
		if (spawnTime > 5)
		{
			switch (rand() % 4)
			{
			case 0: Wizob.setPosition(sf::Vector2f(window.getSize().x / 2, -30.0f));
				break;
			case 1: Wizob.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y + 30.0f));
				break;
			case 2: Wizob.setPosition(sf::Vector2f(-30.0f, window.getSize().y / 2));
				break;
			case 3: Wizob.setPosition(sf::Vector2f(window.getSize().x + 30.0f, window.getSize().y / 2));
				break;
			default:
				break;
			}

			spawnTime = wizobSpawnCounter.restart().asSeconds();
			wizobGroub.push_back(Enemy(Wizob));
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].getMove();
		}
		for (size_t i = 0; i < wizobGroub.size(); i++)
		{
			if (wizobGroub[i].GetCollider().CheckCollision(isaacBodyCollision, 1.0f))
			{
				if(!checkDmg)
				{
					HP[k].setHealth(false);
					checkDmg = true;
				}
				if (HP[k].getHitCount() == 0)
				{
					if (k != 0)
					{
						k--;
					}
				}
				
			}
			Collider wizobCollider = wizobGroub[i].GetCollider();
			for (size_t k = 0; k < bullets.size(); k++)
			{
				if (bullets[k].GetCollider().CheckCollision(wizobCollider, 0.0f))
				{
					wizobGroub[i].setHp(bullets[k].getDmg());
					bullets.erase(bullets.begin() + k);
				}
			}
			if (wizobGroub[i].getHp() <= 0)
			{
				/*if (HP[k].getHitCount() == 2)
				{
					if (k != HP.size() - 1)
						k++;
				}
				HP[k].setHealth(true);
				std::cout << k;*/
				
					switch (rand()%11)
					{
					case 1:ASitem.push_back(Item(AS));
						ASitem[itemCount01].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount01++;
						break;
					case 2:Dmgitem.push_back(Item(Dmg));
						Dmgitem[itemCount02].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount02++;
						break;
					case 3:HBitem.push_back(Item(HB));
						HBitem[itemCount03].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount03++;
						break;
					case 5:Ranitem.push_back(Item(Ran));
						Ranitem[itemCount05].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount05++;
						break;
					case 7:SPitem.push_back(Item(SP));
						SPitem[itemCount07].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount07++;
						break;
					case 8:SCitem.push_back(Item(SC));
						SCitem[itemCount08].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount08++;
						break;
					case 9:SHitem.push_back(Item(SH));
						SHitem[itemCount09].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount09++;
						break;
					case 10:SSBitem.push_back(Item(SSB));
						SSBitem[itemCount10].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount10++;
						break;
					default:
						break;
					}
				score += 10;
				wizobGroub.erase(wizobGroub.begin() + i);
			}
		}
		std::cout << tear.getDmg() << std::endl;
		for (size_t i = 0; i < ASitem.size(); i++)
		{
			if (ASitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				ASitem.erase(ASitem.begin() + i);
				itemCount01--;
				attackSpeed -= 0.05f;
				break;
			}
			Collider asItemCollider = ASitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(asItemCollider, 0.0f))
				{
					ASitem.erase(ASitem.begin() + i);
					itemCount01--;
					break;
				}
			}
		}
		for (size_t i = 0; i < Dmgitem.size(); i++)
		{
			if (Dmgitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				Dmgitem.erase(Dmgitem.begin() + i);
				itemCount02--;
				tear.statDmgUp();
				break;
			}
			Collider dmgItemCollider = Dmgitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(dmgItemCollider, 0.0f))
				{
					Dmgitem.erase(Dmgitem.begin() + i);
					itemCount02--;
					break;
				}
			}
		}
		for (size_t i = 0; i < HBitem.size(); i++)
		{
			if (HBitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				HBitem.erase(HBitem.begin() + i);
				itemCount03--;
				if (HP[k].getHitCount() == 2)
				{
					if (k != HP.size() - 1)
					{
						k++;
					}
				}
				HP[k].setHealth(true);
				break;
			}
			Collider hbItemCollider = HBitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(hbItemCollider, 0.0f))
				{
					HBitem.erase(HBitem.begin() + i);
					itemCount03--;
					break;
				}
			}
		}
		for (size_t i = 0; i < Ranitem.size(); i++)
		{
			if (Ranitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				Ranitem.erase(Ranitem.begin() + i);
				itemCount05--;
				
				switch (rand()%5)
				{
				case 0:
					if (HP[k].getHitCount() == 2)
					{
						if (k != HP.size()-1)
						{
							k++;
						}
					}
					HP[k].setHealth(true);
					break;
				case 1:
					
					if (HP[k].getHitCount() == 0)
					{
						if (k != 0)
						{
							k--;
						}
					}
					HP[k].setHealth(false);
					break;
				case 2:tear.statDmgUp();
					break;
				case 3:attackSpeed -= 0.05f;
					break;
				case 4:attackSpeed += 0.05f;
					break;
				case 5:tear.statDmgDown();
					break;
				default:
					break;
				}
				break;
			}
			Collider ranItemCollider = Ranitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(ranItemCollider, 0.0f))
				{
					Ranitem.erase(Ranitem.begin() + i);
					itemCount05--;
					break;
				}
			}
		}
		for (size_t i = 0; i < SPitem.size(); i++)
		{
			if (SPitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				SPitem.erase(SPitem.begin() + i);
				itemCount07--;
				score += 20;
				break;
			}
			Collider spItemCollider = SPitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(spItemCollider, 0.0f))
				{
					SPitem.erase(SPitem.begin() + i);
					itemCount07--;
					break;
				}
			}
		}
		for (size_t i = 0; i < SCitem.size(); i++)
		{
			if (SCitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				SCitem.erase(SCitem.begin() + i);
				itemCount08--;
				score += 10;
				break;
			}
			Collider scItemCollider = SCitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(scItemCollider, 0.0f))
				{
					SCitem.erase(SCitem.begin() + i);
					itemCount08--;
					break;
				}
			}
		}
		for (size_t i = 0; i < SHitem.size(); i++)
		{
			if (SHitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				SHitem.erase(SHitem.begin() + i);
				itemCount09--;
				score += 10;
				break;
			}
			Collider shItemCollider = SHitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(shItemCollider, 0.0f))
				{
					SHitem.erase(SHitem.begin() + i);
					itemCount09--;
					break;
				}
			}
		}
		for (size_t i = 0; i < SSBitem.size(); i++)
		{
			if (SSBitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				SSBitem.erase(SSBitem.begin() + i);
				itemCount10--;
				score *= 2;
				break;
			}
			Collider ssbItemCollider = SSBitem[i].GetCollider();
			for (int k = 0; k < walls.size(); k++)
			{
				if (walls[k].GetCollider().CheckCollision(ssbItemCollider, 0.0f))
				{
					SSBitem.erase(SSBitem.begin() + i);
					itemCount10--;
					break;
				}
			}
		}
		if (HP[0].getHitCount() == 0)
		{
			playerBody.setPosition(sf::Vector2f(300.0f, 300.0f));
			for (int i = 0; i < HP.size(); i++)
			{
				for (int j = 0; j < 2; j++)
					HP[i].setHealth(true);
			}
			k = HP.size() - 1;
			gameState = 9;
		}
		for (int i = 0; i < walls.size(); i++)
		{
			walls[i].GetCollider().CheckCollision(isaacBodyCollision, 1.0f);
		}
		for (auto& wall : walls)
			wall.Draw(window);
		playerBody.Update(deltaTime);
		tear.Update(deltaTime, playerBody.GetPosition(), sf::Vector2f(25.0f, 25.0f), sf::Mouse::getPosition(window));
		window.draw(map01);
		if (timing >= 2)
		{
			timing=dmgCheck.restart().asSeconds();
			checkDmg = false;
		}
		if(checkDmg)
		{
			if (rand() % 2 == 0)
				playerBody.Draw(window);
		}
		else
		{
			playerBody.Draw(window);
		}
		for (size_t i = 0; i < wizobGroub.size(); i++)
		{
			if(i!=0)
			{
				wizobGroub[i].enemyUpdate(deltaTime, playerBody.GetPosition());
				wizobGroub[i].Draw(window);
			}
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].Draw(window);
		}
		for (size_t i = 0; i < HP.size(); i++)
		{
			HP[i].Update(deltaTime, 20, sf::Vector2f(40.0f * (i + 1), 48.0f));
			HP[i].Draw(window);
		}
			for (size_t i = 0; i < ASitem.size(); i++)
			{
					ASitem[i].Draw(window);
			}
			for (size_t i = 0; i < Dmgitem.size(); i++)
			{
					Dmgitem[i].Draw(window);
			}
			for (size_t i = 0; i < HBitem.size(); i++)
			{
					HBitem[i].Draw(window);
			}
			for (size_t i = 0; i < Ranitem.size(); i++)
			{
					Ranitem[i].Draw(window);
			}
			for (size_t i = 0; i < SPitem.size(); i++)
			{
					SPitem[i].Draw(window);
			}
			for (size_t i = 0; i < SCitem.size(); i++)
			{
				if(i!=0)
					SSBitem[i].Draw(window);
			}
			window.display();
		}
		if (gameState == 3)
		{
			window.clear();
			window.display();
		}
		if (gameState == 9)
		{
			userScore[0].second = nameInput.getText();
			userScore[0].first = score;
			

			for (size_t i = 0; i < wizobGroub.size(); i++)
			{
				if(i!=0)
				wizobGroub.erase(wizobGroub.begin() + i);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				
				gameState = 0;
			}
			sort(userScore.begin(), userScore.end());
			fopen("Score.txt", "w");
			for (size_t i = 5; i >= 1; i--)
			{
				strcpy(playerName, userScore[i].second.c_str());
				fprintf(scoreFile, "%s %d\n", playerName, userScore[i].first);
			}
			fclose(scoreFile);

			window.clear();
			showHighScore(10, 10, "SCORE", window, &font);
			showHighScore(10, 40, nameInput.getText(), window, &font);
			showHighScore(10, 70, std::to_string(score), window, &font);
			window.display();

		}
	}//πÕ° loop while window open ‚«È¬¬¬¬ ‰ÕÈß—Ëßß
	
	return 0;
}

bool randomItemSpwanRate(int dropRate)
{
	switch (rand() % dropRate)
	{
	case 0: return true;
	default: return false;
	}
}
void showHighScore(int x, int y, std::string word, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}

