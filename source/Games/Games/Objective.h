// Obejctive screen class.
// Used to inform the player of the objective of the game.
#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include <string.h>
#include "States.h"
#include "StaticSprite.h"
#include "Cursor.h"

class Objective
{
public:
	Objective(sf::RenderWindow* hwnd, Input* in, sf::View* vi);
	~Objective();

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

	StaticSprite objectiveImage;
	StaticSprite backButtonImage;
	sf::Texture texture;
	sf::Texture texture2;

	Cursor cursor;
};
