// Controls screen class.
// Used to display the controls of the game to the player.
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"
#include "StaticSprite.h"
#include "Cursor.h"

class Controls
{
public:
	Controls(sf::RenderWindow* hwnd, Input* in, sf::View* vi);
	~Controls();

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

	StaticSprite controlsImage;
	StaticSprite backButtonImage;
	sf::Texture texture;
	sf::Texture texture2;

	Cursor cursor;
};
