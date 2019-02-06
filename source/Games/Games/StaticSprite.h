// StaticSprite class
// Used for sprites that dont need to move/be animated (e.g. Menu sprites)
#pragma once
#include "Sprites.h"

class StaticSprite : public Sprites
{
public:
	StaticSprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~StaticSprite();

	void update(float dt);
	void collisionResponse();

protected:
	sf::Texture texture;
	sf::Vector2f position;
};

