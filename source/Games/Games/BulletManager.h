// Bullet Manager.
// Maintains vector of Bullets for spawning in game.
#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Cursor.h"
#include "Vector.h"
#include <math.h>
#include <vector>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void spawn();
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);
	void reset();
	void getPlayer(Player* player);
	void getCursor(Cursor* cursor);
	std::vector<Bullet>* getBulletVector() { return &bullets; };

private:
	std::vector<Bullet> bullets;
	sf::Vector2f spawnPoint;
	sf::Vector2f target;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Texture texture;
	float rotation;
	float speed;
	Player* player;
	Cursor* cursor;
};

