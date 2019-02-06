// Blood class.
// Manipulated by Blood Manager.
#pragma once
#include "Sprites.h"

class Blood : public Sprites
{
private:
	sf::Vector2f position;
public:
	Blood(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Blood();

	void update(float dt);
};

