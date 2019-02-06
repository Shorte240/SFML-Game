// Enemy class.
// Manipulated by Enemy Manager.
#pragma once
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Input.h"
#include "Vector.h"

class Enemy : public AnimatedSprite
{
	
public:
	Enemy(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Enemy();

	void update(float dt);
	void setMoving(bool moving);
	bool getMoving() { return moving; };
	Animation* getCurrentAnimation() { return &walk; };
	void setElapsedTime(float time);
	float getElapsedTime() { return elapsedTime; };
	void worldCollisionResponse(Sprites* sp);
	void largeCollisionResponse(Sprites* sp);

protected:
	sf::Vector2f position;
	bool moving;
	float elapsedTime;
	Animation walk;
};