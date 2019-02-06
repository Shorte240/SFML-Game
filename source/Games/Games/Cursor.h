// Cursor class.
// Gives new sprite instead of default mouse pointer.
#pragma once
#include "Sprites.h"
#include "Input.h"

class Cursor : public Sprites
{
private:
	Input* input;
	sf::Texture texture;
	sf::Vector2f position;
public:
	Cursor(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Cursor();

	void update(float dt);
	void getInput(Input *input);
};

