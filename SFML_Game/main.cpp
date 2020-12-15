#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<SFML/Audio.hpp>
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
#include"Button.h"
bool randomItemSpwanRate(int dropRate);
void showHighScore(int x, int y, std::string word, sf::RenderWindow& window, sf::Font* font, int size);

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
	window.setFramerateLimit(60);
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

	scoreFile = fopen("./Score.txt","r");
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

	fopen("./Score.txt", "w");
	for (size_t i = 5; i >= 1; i--)
	{
		strcpy(playerName, userScore[i].second.c_str());
		fprintf(scoreFile, "%s %d\n", playerName, userScore[i].first);
	}
	fclose(scoreFile);

	sf::RectangleShape mouseCursor;
	sf::RectangleShape pauseBG;
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
	sf::Texture grayBG;
	sf::Texture howto;
	sf::Texture leaderBoardAni;
	sf::Texture hush;
	sf::Texture bone;
	sf::Texture map02;
	sf::Texture map03;
	sf::Texture map04;
	map02.loadFromFile("./Resource/Map/Map02.png");
	map03.loadFromFile("./Resource/Map/Map03.png");
	map04.loadFromFile("./Resource/Map/Map04.png");
	isacTexture.loadFromFile("./Resource/Player/IsaacPlayer.png");
	map.loadFromFile("./Resource/Map/Map01.png");
	lost.loadFromFile("./Resource/gfx/playerportraitbig_12_thelost.png");
	pic.loadFromFile("./Resource/gfx/playerportraitbig_01_isaac.png");
	lightFX.loadFromFile("./Resource/gfx/the_marshall_light.png");
	menuBG.loadFromFile("./Resource/Map/MenuBG.png");
	hpbar.loadFromFile("./Resource/Item/hearts.png");
	enemy01.loadFromFile("./Resource/Enemy/Wizob.png");
	tearIsaac.loadFromFile("./Resource/Tear/Tear0.png");
	grayBG.loadFromFile("./Resource/gfx/Untitled-1.png");
	howto.loadFromFile("./Resource/gfx/howtoplay.png");
	leaderBoardAni.loadFromFile("./Resource/gfx/PlayerPortraitBig_Keeper.png");
	hush.loadFromFile("./Resource/gfx/playerportraitbig_06_bluebaby.png");
	bone.loadFromFile("./Resource/gfx/playerportraitbig_16_theforgotten.png");
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
	//ASitem.push_back(Item(AS));
	std::vector<Item> Dmgitem;
	//Dmgitem.push_back(Item(Dmg));
	std::vector<Item> HBitem;
	//HBitem.push_back(Item(HB));
	std::vector<Item> HDitem;
	//HDitem.push_back(Item(HD));
	std::vector<Item> Ranitem;
	//Ranitem.push_back(Item(Ran));
	std::vector<Item> RWitem;
	//RWitem.push_back(Item(RW));
	std::vector<Item> SPitem;
	//SPitem.push_back(Item(SP));
	std::vector<Item> SCitem;
	//SCitem.push_back(Item(SC));
	std::vector<Item> SHitem;
	//SHitem.push_back(Item(SH));
	std::vector<Item> SSBitem;
	//SSBitem.push_back(Item(SSB));
	std::vector<Item> TSitem;
	//TSitem.push_back(Item(TS));
	std::vector<Item> ZWitem;
	//ZWitem.push_back(Item(ZW));
	///////////////////////
	sf::RectangleShape theLost(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape xiaO(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape keeper(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape hushh(sf::Vector2f(100.0f, 100.0f));
	sf::RectangleShape menuBackground(sf::Vector2f(936, 624));
	sf::RectangleShape lightfx(sf::Vector2f(96*1.5, 256*1.5));
	sf::RectangleShape forgotten(sf::Vector2f(150.0f, 150.0f));
	sf::RectangleShape map01(sf::Vector2f(936, 624));
	sf::RectangleShape Map02(sf::Vector2f(936, 624));
	sf::RectangleShape Map03(sf::Vector2f(936, 624));
	sf::RectangleShape Map04(sf::Vector2f(936, 624));
	sf::RectangleShape frame(sf::Vector2f(1080.0f, 1000.0f));
	sf::RectangleShape howtoplay(sf::Vector2f(window.getSize().x,window.getSize().y));
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_HEIGHT, View_HEIGHT));

	Bullet tear(&tearIsaac, sf::Vector2u(1, 1), 3.0f, 1.0f);
	Enemy Wizob(&enemy01, sf::Vector2u(4, 3), 0.25f, 0.5f);
	healthbar health(&hpbar, sf::Vector2u(1, 3), 3.0f, 200.0f);
	Menu menu(window.getSize().x, window.getSize().y);
	Player playerBody(&isacTexture, sf::Vector2u(9, 6), 0.1f, 100.0f, window);
	Textbox nameInput(32, sf::Color::White, false);
	Button pauseButton(&font,32,window.getSize().x,window.getSize().y);
	
	std::vector<Bullet> bullets;
	std::vector<Enemy> wizobGroub;
	std::vector<healthbar> HP;

	bullets.push_back(Bullet(tear));
	//wizobGroub.push_back(Enemy(Wizob));
	for (int i = 0; i < 3; i++)
		HP.push_back(healthbar(health));

	forgotten.setTexture(&bone);
	hushh.setTexture(&hush);
	keeper.setTexture(&leaderBoardAni);
	howtoplay.setTexture(&howto);
	theLost.setTexture(&lost);
	xiaO.setTexture(&pic);
	menuBackground.setTexture(&menuBG);
	lightfx.setTexture(&lightFX);
	map01.setTexture(&map);
	Map02.setTexture(&map02);
	Map03.setTexture(&map03);
	Map04.setTexture(&map04);

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
	sf::Clock difficulty;

	int gameState = 0;
	bool checkDmg = false;
	int score = 0;
	float spawnTime;
	float difficultyRate;
	float shootDelay = 0.0f;
	float deltaTime = 0.0f;
	float attackSpeed = 1.0f;
	int k = HP.size() - 1;
	int timing;
	int roomSummonState=0;
	int musicState = 0 ;
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

	sf::Text scoreDisplay;
	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(32);
	scoreDisplay.setString("Score : ");
	scoreDisplay.setPosition(40, 60);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setString(std::to_string(score));
	scoreText.setPosition(160, 60);

	sf::Text difficultText;
	difficultText.setFont(font);
	difficultText.setCharacterSize(32);
	difficultText.setString("Difficulty : ");
	difficultText.setPosition(40, 90);

	sf::Text difficultRateText;
	difficultRateText.setFont(font);
	difficultRateText.setCharacterSize(32);
	difficultRateText.setPosition(260, 90);

	sf::Text pausemenu;
	pausemenu.setFont(font);
	pausemenu.setCharacterSize(64);
	pausemenu.setString("PAUSE");
	pausemenu.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/3));
	pausemenu.setOrigin(pausemenu.getLocalBounds().width / 2, pausemenu.getLocalBounds().height);

	pauseBG.setTexture(&grayBG);
	pauseBG.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Music titlemusic;
	titlemusic.openFromFile("./Resource/sfx/title screen.ogg");
	titlemusic.setLoop(true);
	titlemusic.setVolume(15.0f);

	sf::Music gamemusic;
	gamemusic.openFromFile("./Resource/sfx/the womb chapter four.ogg");
	gamemusic.setLoop(true);
	gamemusic.setVolume(15.0f);

	sf::SoundBuffer hurtsfx;
	hurtsfx.loadFromFile("./Resource/sfx/baby hurt 1.wav");
	sf::Sound hurt;
	hurt.setBuffer(hurtsfx);
	hurt.setVolume(15.0f);

	sf::SoundBuffer diesfx;
	diesfx.loadFromFile("./Resource/sfx/isaac dies new 1.wav");
	sf::Sound die;
	die.setBuffer(diesfx);
	die.setVolume(15.0f);

	sf::SoundBuffer wizobroar;
	wizobroar.loadFromFile("./Resource/sfx/ghost shoot 2.wav");
	sf::Sound roar;
	roar.setBuffer(wizobroar);
	roar.setVolume(10.0f);

	sf::SoundBuffer ghostdie;
	ghostdie.loadFromFile("./Resource/sfx/ghost roar.wav");
	sf::Sound ghostsfx;
	ghostsfx.setBuffer(ghostdie);
	ghostsfx.setVolume(10.0f);

	sf::SoundBuffer tearSfx;
	tearSfx.loadFromFile("./Resource/sfx/tear fire 4.wav");
	sf::Sound tearsfx;
	tearsfx.setBuffer(tearSfx);
	tearsfx.setVolume(15.0f);

	sf::SoundBuffer summonSfx;
	summonSfx.loadFromFile("./Resource/sfx/summonsound.wav");
	sf::Sound summon;
	summon.setBuffer(summonSfx);
	summon.setVolume(15.0f);

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
			if (musicState == 0)
			{
				gamemusic.stop();
				titlemusic.play();
				musicState++;
			}
			
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
				gameState = 5;
			}
			else if (menu.getState() == 3 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.close();
				return 0;
			}
			
			lightfx.setPosition(sf::Vector2f(85.0f, 0.0f));
			xiaO.setPosition(sf::Vector2f(110.0f, 235.0f));
			theLost.setPosition(sf::Vector2f(110.0f, 205.0f));
			keeper.setPosition(sf::Vector2f(110.0f, 235.0f));
			hushh.setPosition(sf::Vector2f(110.0f, 235.0f));
			window.clear();
			window.draw(menuBackground);
			if(rand()%50!=0&& menu.getState() != 0&& menu.getState() != 1 && menu.getState() != 2 && menu.getState() != 3)
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
			if (menu.getState() == 1)
			{
				if (rand() % 10 != 0)
				{
					window.draw(keeper);
					window.draw(lightfx);
				}

			}
			if (menu.getState() == 2)
			{
				if (rand() % 10 != 0)
				{
					window.draw(hushh);
					window.draw(lightfx);
				}

			}
			if (menu.getState() == 3)
			{
				if (rand() % 10 != 0)
				{
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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				nameInput.setSelected(false);
				gameState = 0;
			}
			
			nameInput.setPosition(sf::Vector2f(20, window.getSize().y*1/3+32));
			window.clear();
			window.draw(menuBackground);
			showHighScore(110, window.getSize().y * 1 / 3, "Input Name", window, &font, 32);
			nameInput.drawTo(window);
			window.display();
		}
		if (gameState == 2)
		{
			if (musicState == 1)
			{
				gamemusic.play();
				titlemusic.stop();
				musicState++;
			}
			
			difficultyRate = difficulty.getElapsedTime().asSeconds();
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
			int spawnRate = 5 - difficultyRate/120;
			if (spawnRate < 1) spawnRate = 1;
		if (spawnTime > spawnRate)
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
			roar.play();
			spawnTime = wizobSpawnCounter.restart().asSeconds();
			Wizob.getDifficult(difficultyRate);
			if(wizobGroub.size()<=5)
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
					if (k != 0 && HP[0].getHitCount() != 1)
						hurt.play();
					else
						die.play();
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
					tearsfx.play();
					wizobGroub[i].setHp(bullets[k].getDmg());
					bullets.erase(bullets.begin() + k);
					
				}
			}
			if (wizobGroub[i].getHp() <= 0)
			{
					switch (rand()%11)
					{
					case 1:ASitem.push_back(Item(AS));
						ASitem[itemCount01].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount01++;
						break;
					case 2:if (rand() % 5 == 0)
					{
						Dmgitem.push_back(Item(Dmg));
						Dmgitem[itemCount02].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount02++;

					}
						break;
					case 3:if (rand() % 3 == 0)
					{ 

						HBitem.push_back(Item(HB));
						HBitem[itemCount03].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount03++;
					}
						break;
					case 5:Ranitem.push_back(Item(Ran));
						Ranitem[itemCount05].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount05++;
						break;
					case 7:if(rand()%2==0)
					{
						SPitem.push_back(Item(SP));
						SPitem[itemCount07].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount07++;
						
					}break;
						
					case 8:SCitem.push_back(Item(SC));
						SCitem[itemCount08].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount08++;
						break;
					case 10:if (rand() % 5 == 0)
					{
						SSBitem.push_back(Item(SSB));
						SSBitem[itemCount10].Update(deltaTime, wizobGroub[i].GetPosition());
						itemCount10++;
					}
						break;
					/*default:
						break;*/
					}
					ghostsfx.play();
				score += 10;
				if (!wizobGroub.empty()) {
					wizobGroub.erase(wizobGroub.begin() + i);
				}
			}
		}
		for (size_t i = 0; i < ASitem.size(); i++)  
		{
			if (ASitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				ASitem.erase(ASitem.begin() + i);
				itemCount01--;
				if(attackSpeed>0.25f)
				attackSpeed -= 0.05f;
				continue;
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
				continue;
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
				continue;
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
				switch (rand()%8)
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
				case 6:
					if(rand()%7)
					wizobGroub.erase(wizobGroub.begin(), wizobGroub.end());
					break;
				default:
					break;
				}
				continue;
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
				continue;
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
				continue;
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
		for (size_t i = 0; i < SSBitem.size(); i++)
		{
			if (SSBitem[i].GetCollider().CheckCollision(isaacBodyCollision, 0.0f))
			{
				SSBitem.erase(SSBitem.begin() + i);
				itemCount10--;
				score *= 2;
				continue;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameState = 4;
		}
		for (int i = 0; i < walls.size(); i++)
		{
			walls[i].GetCollider().CheckCollision(isaacBodyCollision, 1.0f);
		}
		int rate = difficultyRate / 60;
		for (auto& wall : walls)
			wall.Draw(window);
		playerBody.Update(deltaTime);
		tear.Update(deltaTime, playerBody.GetPosition(), sf::Vector2f(25.0f, 25.0f), sf::Mouse::getPosition(window));
		if(rate%4==0)
		{
			if (roomSummonState == 0)
			{
				summon.play();
				roomSummonState++;
			}
			window.draw(map01);
		}
		else if (rate % 4 == 1)
		{	
			if (roomSummonState == 1)
			{
				summon.play();
				roomSummonState++;
			}
			window.draw(Map02);
		}
		else if (rate % 4 == 2)
		{
			if (roomSummonState == 2)
			{
				summon.play();
				roomSummonState++;
			}
			window.draw(Map03);
		}
		else if (rate % 4 == 3)
		{
			if (roomSummonState == 3)
			{
				summon.play();
				roomSummonState=0;
			}
			window.draw(Map04);
		}
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
				wizobGroub[i].enemyUpdate(deltaTime, playerBody.GetPosition());
				wizobGroub[i].Draw(window);
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
			for (size_t i = 0; i < SSBitem.size(); i++)
			{
					SSBitem[i].Draw(window);
			}
			for (size_t i = 0; i < SCitem.size(); i++)
			{
				SCitem[i].Draw(window);
			}
			
			difficultRateText.setString(std::to_string(rate));
			scoreText.setString(std::to_string(score));
			window.draw(scoreDisplay);
			window.draw(scoreText);
			window.draw(difficultText);
			window.draw(difficultRateText);
			window.display();
		}
		if (gameState == 3)
		{
			sort(userScore.begin(), userScore.end());
			window.clear();
			showHighScore(window.getSize().x / 2,20, "LEADERBOARD", window, &font,72);
			for (size_t i = 5; i >= 1; i--)
			{
				showHighScore(window.getSize().x *2/ 6, 120+(50*(5-i)), userScore[i].second.c_str(), window, &font,40);
				showHighScore(window.getSize().x*4 / 6, 120 + (50 *(5- i)), std::to_string(userScore[i].first), window, &font,40);
			}
			showHighScore(210, window.getSize().y-50, "Press ESC to go back . . .", window, &font, 32);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameState = 0;
			}
			window.display();
		}
		if(gameState == 4)
		{
			pauseButton.Update(sf::Vector2f(sf::Mouse::getPosition(window)));
			
			if (pauseButton.getSelect()==0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameState = 2;
			}
			else if (pauseButton.getSelect()==1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameState = 9;
			}
			window.draw(pauseBG);
			window.draw(pausemenu);
			pauseButton.Draw(window);
			window.display();
		}
		if (gameState == 5)
		{
			howtoplay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameState = 0;
			}
			window.clear();
			window.draw(howtoplay);
			showHighScore(210, window.getSize().y - 50, "Press ESC to go back . . .", window, &font, 32);
			window.display();
		}
		if (gameState == 9)
		{
			musicState = 0;
			if (wizobGroub.size() != 0)
			{
				wizobGroub.erase(wizobGroub.begin(), wizobGroub.end());
			}
			difficultyRate = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				userScore.erase(userScore.begin(), userScore.end());
				scoreFile = fopen("./Score.txt", "r");
				for (int i = 0; i < 5; i++)
				{
					fscanf(scoreFile, "%s", &playerName);
					name[i] = playerName;
					fscanf(scoreFile, "%d", &playerScore[i]);
					userScore.push_back(make_pair(playerScore[i], name[i]));
				}
				fclose(scoreFile);
				userScore[0].second = nameInput.getText();
				userScore[0].first = score;
				userScore.push_back(make_pair(playerScore[0], name[0]));
				sort(userScore.begin(), userScore.end());
				

				fopen("./Score.txt", "w");
				for (size_t i = 5; i >= 1; i--)
				{
					strcpy(playerName, userScore[i].second.c_str());
					fprintf(scoreFile, "%s %d\n", playerName, userScore[i].first);
				}
				fclose(scoreFile);

				gameState = 0;
			}
			window.clear();
			forgotten.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y *2/ 3));
			forgotten.setOrigin(sf::Vector2f(forgotten.getSize().x / 2, forgotten.getSize().y / 2));
			window.draw(forgotten);
			showHighScore(window.getSize().x/2, window.getSize().y *1/ 5, "SCORE", window, &font, 108);
			showHighScore(window.getSize().x / 2, window.getSize().y * 2 / 5, nameInput.getText(), window, &font, 32);
			showHighScore(window.getSize().x / 2, (window.getSize().y * 2 / 5)+30, std::to_string(score), window, &font, 32);
			showHighScore(window.getSize().x -250, window.getSize().y-50, "Press Enter to continue . . .", window, &font, 32);
			window.display();
		}
		
	}//πÕ° loop while window open ‚«È¬¬¬¬ ‰ÕÈß—Ëß
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
void showHighScore(int x, int y, std::string word, sf::RenderWindow& window, sf::Font* font,int size)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(sf::Vector2f(x, y));
	text.setString(word);
	text.setCharacterSize(size);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	window.draw(text);
}

