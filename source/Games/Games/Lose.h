// Lose screen class
// What is displayed if the player loses the game.
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"
#include "StaticSprite.h"
#include "Cursor.h"
#include "AudioManager.h"

class Lose
{
public:
	Lose(sf::RenderWindow* hwnd, Input* in, sf::View* vi);
	~Lose();

	void handleInput(float dt);
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

	StaticSprite loseImage;
	StaticSprite continueButtonImage;
	sf::Texture texture;
	sf::Texture texture2;
	AudioManager audioMgr;
	bool hasStarted = false;

	Cursor cursor;
};
