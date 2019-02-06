// Game 2/Level 2
// Collates classes to provide a game for the player.
#pragma once

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Player.h"
#include "Cursor.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "BloodManager.h"
#include "Map.h"
#include "Tile.h"
#include "States.h"
#include "AudioManager.h"
#include<Windows.h>
#include<string.h>
#include<vector>

using namespace std;

class Game2
{
public:
	Game2(sf::RenderWindow* hwnd, Input *input, sf::View* vi);
	~Game2();

	//Functions
	void handleInput(float dt);
	void update(float dt);
	void render();
	void reset();
	GameState getState();
	GameState getPreviousState();

private:
	bool checkCollision(Sprites* s1, Sprites* s2);
	bool checkSphereBounding(Sprites* s1, Sprites* s2);
	bool checkLargeSphereBounding(Sprites* s1, Sprites* s2);

	//Background setup
	sf::RenderWindow* window;
	sf::View* view;
	Input* input;
	GameState state;
	GameState previousState;

	//HUD Rect
	sf::RectangleShape rect;

	//Text setup
	sf::Font font;
	sf::Text healthText;
	sf::Text bulletsText;
	sf::Text clipsText;
	sf::Text zombiesKilledText;
	sf::View HUD;

	//Entity setup
	Player player;
	Cursor cursor;
	EnemyManager enemyManager;
	BulletManager bulletManager;
	BloodManager bloodManager;
	AudioManager audioMgr;
	Map level;

	//Variables
	float t = 0;
	bool hasStarted = false;

	//Draw functions
	void beginDraw();
	void endDraw();
};

