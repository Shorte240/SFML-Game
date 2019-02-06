// Bullet class.
// Manipulated by Bullet Manager.
#pragma once
#include "Sprites.h"
#include "Input.h"

class Bullet : public Sprites
{
private:
	sf::Vector2f position;
public:
	Bullet(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Bullet();

	void update(float dt);
};
