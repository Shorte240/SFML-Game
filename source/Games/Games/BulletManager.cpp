#include "BulletManager.h"

BulletManager::BulletManager()
{
	//some default values
	spawnPoint = sf::Vector2f(100.f, 100.f);
	rotation = 0.f;
	target = sf::Vector2f(600.f, 300.f);
	speed = 500.f;
	texture.loadFromFile("gfx/Bullet.png");

	for (int i = 0; i < 40; i++)
	{
		bullets.push_back(Bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&texture);
		bullets[i].setSize(sf::Vector2f(8.f, 8.f));
	}
}

BulletManager::~BulletManager()
{
}

void BulletManager::update(float dt)
{
	//Update certain values
	spawnPoint = sf::Vector2f(player->getPosition()); //Spawn at players location.
	rotation = player->getRotation(); //Get players rotation.
	target = sf::Vector2f(cursor->getPosition()); //Update target to cursors position.
	direction = target - spawnPoint; //Set directional vector.
	direction = Vector::normalise(direction);
	velocity = (direction * speed);

	//call update on all ALIVE bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt);
			bullets[i].updateAABB();
		}
	}
	deathCheck();
}

//Spawn new bullet
//Find a "dead" bullet, make alive, move to spawn point, give set velocity
void BulletManager::spawn()
{
	while (player->getBullets() > 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets[i].isAlive())
			{
				player->setBullets(player->getBullets() - 1); //Decrease players bullet count by 1.
				bullets[i].setAlive(true);
				bullets[i].setPosition(spawnPoint);
				bullets[i].setRotation(rotation);
				bullets[i].setVelocity(velocity);
				return;
			}
		}

		if (player->getBullets() == 0)
		{
			player->setBullets(0);
		}
	}
	
}

//Check all ALIVE bullets to see if outside screen/range, if so make dead
void BulletManager::deathCheck()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < -100.f)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > 1600.f)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < -100.f)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > 1200.f)
			{
				bullets[i].setAlive(false);
			}
		}
	}
}

//Render all alive bullets
void BulletManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
}

void BulletManager::getPlayer(Player* play)
{
	player = play;
}

void BulletManager::getCursor(Cursor* cur)
{
	cursor = cur;
}

void BulletManager::reset()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].setAlive(false);
	}
}