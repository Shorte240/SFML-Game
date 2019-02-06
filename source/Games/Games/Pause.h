// Pause screen class.
// Used to pause the game.
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"
#include "StaticSprite.h"
#include "Cursor.h"

class Pause
{
public:
	Pause(sf::RenderWindow* hwnd, Input* in, sf::View* vi);
	~Pause();

	void handleInput(float dt);
	void render();
	GameState getState();
	GameState getPreviousState();
	void setPreviousState(GameState v);

private:
	bool checkCollision(Sprites* s1, Sprites* s2);
	void beginDraw();
	void endDraw();
	sf::RenderWindow* window;
	Input* input;
	GameState state;
	GameState previousState;
	sf::View* view;

	StaticSprite logo;
	StaticSprite resumeButtonImage;
	StaticSprite quitButtonImage;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Texture texture3;

	Cursor cursor;
};



