// Enemy Manager
// Maintains vector of Enemies for spawning in game.
#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Vector.h"
#include "Blood.h"
#include <math.h>
#include <vector>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void spawn();
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);
	void getPlayer(Player* player);
	void reset();
	std::vector<Enemy>* getEnemyVector() { return &enemies; };

private:
	std::vector<Enemy> enemies;
	sf::Vector2f spawnPoint;
	sf::Texture texture;
	sf::Vector2f target;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f pos;
	sf::IntRect frame;
	Player* player;
	float speed;
	float rotation;
	const float PI = 3.14159265;
};

