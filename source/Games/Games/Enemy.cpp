#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f & size) : AnimatedSprite(size)
{
	walk.init(0, 0, 12, 9, 4, 0.1f);
	elapsedTime = 0.f;
}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
}

void Enemy::setMoving(bool eMoving)
{
	moving = eMoving;
}

void Enemy::setElapsedTime(float time)
{
	elapsedTime = time;
}

void Enemy::worldCollisionResponse(Sprites* sp)
{
	if ((abs(sp->getPosition().x + sp->getAABB().width / 2 - getPosition().x)) > (abs(sp->getPosition().y + sp->getAABB().width / 2 - getPosition().y)))
	{
		//Left or Right Side collision
		if (getPosition().x < sp->getPosition().x)
		{
			//Left side collision
			setPosition(sp->getPosition().x - getSize().x + getOrigin().x, getPosition().y);
		}
		else
		{
			//Right side collision
			setPosition(sp->getPosition().x + sp->getSize().x + getOrigin().x, getPosition().y);
		}
	}
	else
	{
		//Top or Bottom collision
		if (getPosition().y < sp->getPosition().y)
		{
			//Top side collision
			setPosition(getPosition().x, sp->getPosition().y - getSize().y + getOrigin().y);
		}
		else
		{
			//Bottom side collision
			setPosition(getPosition().x, sp->getPosition().y + sp->getSize().y + getOrigin().y);
		}
	}
}

void Enemy::largeCollisionResponse(Sprites* sp)
{
	moving = true;
}

