#pragma once
#include "SFML\Graphics.hpp"

class Sprites : public sf::RectangleShape
{
public:
	Sprites(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprites();

	virtual void update(float dt) = 0;
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	void setAlive(bool live) { alive = live; };
	bool isAlive() { return alive; };
	sf::Vector2f getVelocity();

	sf::FloatRect getAABB();
	virtual void updateAABB();
	virtual void updateAABBWithOrigin();
	virtual void collisionResponse();

protected:
	sf::Vector2f velocity;
	sf::FloatRect AABB;
	bool alive;
};

