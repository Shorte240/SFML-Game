// Class to represent tile.
// Static sprite, must inherit from Sprite due to Pure Virtual Function

#pragma once
#include "Sprites.h"

class Tile : public Sprites
{
public:
	Tile(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Tile();

	void update(float dt);	
};

