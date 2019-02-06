#include "StaticSprite.h"

StaticSprite::StaticSprite(const sf::Vector2f & size) : Sprites(size)
{
}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::update(float dt)
{
	updateAABB();
}

void StaticSprite::collisionResponse()
{
}
