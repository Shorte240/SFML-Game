#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f & size) : Sprites(size)
{
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	move(velocity*dt);
}
