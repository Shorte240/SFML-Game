// Menu class
// First state/screen displayed to the player
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"
#include "StaticSprite.h"
#include "Cursor.h"
#include "AudioManager.h"

class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, sf::View* vi);
	~Menu();

	void handleInput(float dt);
	void update(float dt);
	void render();
	GameState getState();

private:
	bool checkCollision(Sprites* s1, Sprites* s2);
	void beginDraw();
	void endDraw();
	sf::RenderWindow* window;
	Input* input;
	GameState state;
	sf::View* view;

	StaticSprite logo;
	StaticSprite playButtonImage;
	StaticSprite controlsButtonImage;
	StaticSprite objectiveButtonImage;
	StaticSprite quitButtonImage;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;

	Cursor cursor;
	AudioManager audioMgr;

	bool hasStarted = false;
	int randy;
};

