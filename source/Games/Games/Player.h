// Player class
// Used to control the player.
#pragma once
#include "AnimatedSprite.h"
#include "Animation.h"
#include "Input.h"
#include "Vector.h"

class Player : public AnimatedSprite
{
public:
	Player(const sf::Vector2f &size = sf::Vector2f(0, 0));
	~Player();

	void update(float dt);
	void getInput(Input *input);
	void worldCollisionResponse(Sprites* sp);
	void enemyCollisionResponse(Sprites* sp);
	int getHealth() { return health; };
	int getBullets() { return bullets; };
	int getClips() { return clips; };
	int getZombiesKilled() { return zombiesKilled; };
	void setHealth(int pHealth);
	void setBullets(int pBullets);
	void setClips(int pClips);
	void setZombiesKilled(int pZK);
	void reset();

protected:
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f target;
	sf::Vector2f pos;
	float rotation;
	const float PI = 3.14159265;
	bool notFlipped = true;
	int health;
	int bullets;
	int clips;
	int zombiesKilled;
	Input* input;
	Animation walk;
	Animation* currentAnimation;
};
