#include "Cursor.h"

Cursor::Cursor(const sf::Vector2f & size) : Sprites(size)
{
	texture.loadFromFile("gfx/Crosshairs.png");
	setSize(sf::Vector2f(36.f, 36.f));
	setTexture(&texture);
	setPosition(100.f, 100.f);
	setOrigin(getSize().x / 2.f, getSize().y / 2.f);
	updateAABBWithOrigin();
}

Cursor::~Cursor()
{
}

void Cursor::update(float dt)
{
	setPosition(input->getMouseWorld());
	position = input->getMouseWorld();
	updateAABBWithOrigin();
}

void Cursor::getInput(Input *in)
{
	input = in;
}
