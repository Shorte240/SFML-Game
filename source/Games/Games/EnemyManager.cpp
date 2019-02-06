#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	//Default values for enemies
	spawnPoint = sf::Vector2f(350.f, 350.f);
	target = sf::Vector2f(600.f, 300.f);
	texture.loadFromFile("gfx/EnemySprite.png");
	speed = 125.f;

	for (int i = 0; i < 20; i++)
	{
		enemies.push_back(Enemy());
		enemies[i].setAlive(false);
		enemies[i].setMoving(false);
		enemies[i].setTexture(&texture);
		frame = enemies[i].getCurrentAnimation()->getCurrentFrame();
		enemies[i].setTextureRect(frame);
		enemies[i].setSize(sf::Vector2f(36.f, 36.f));
		enemies[i].setOrigin(enemies[i].getSize().x / 2.f, enemies[i].getSize().y / 2.f);
		enemies[i].updateAABBWithOrigin();
	}
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::update(float dt)
{
	spawnPoint = sf::Vector2f(rand() % 1600, rand() % 1200); //Random spawn location on map
	target = (player->getPosition()); //Update target as players position.
	//call update on all ALIVE enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (enemies[i].getMoving())
			{
				direction = target - enemies[i].getPosition();
				direction = Vector::normalise(direction);
				velocity = (direction * speed);
				pos = enemies[i].getPosition() - target;
				pos = Vector::normalise(pos);
				float dx = pos.x;
				float dy = pos.y;

				rotation = (atan2(dy, dx)) * 180.f / PI;

				rotation -= 90.f;

				enemies[i].setRotation(rotation);
				enemies[i].move(velocity*dt);

				//increment time
				enemies[i].setElapsedTime(enemies[i].getElapsedTime() + dt);

				//if enough time has passed move onto next frame
				if (enemies[i].getElapsedTime() >= enemies[i].getCurrentAnimation()->getAnimationTime())
				{
					//next frame
					enemies[i].getCurrentAnimation()->nextFrame();
					enemies[i].setTextureRect(enemies[i].getCurrentAnimation()->getCurrentFrame());
					enemies[i].setElapsedTime(0.f);
				}
			}

			//if object is close enough to target
			if (Vector::magnitude(target - enemies[i].getPosition()) < 10.f)
			{
				enemies[i].setMoving(false);
			}
			enemies[i].updateAABBWithOrigin();
			enemies[i].update(dt);
		}
	}
	deathCheck();
}

//Spawn new enemies
//Find a "dead" enemy, make alive, move to spawn point
void EnemyManager::spawn()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].isAlive())
		{
			enemies[i].setAlive(true);
			enemies[i].setPosition(spawnPoint);
			return;
		}
	}
}

//Check all ALIVE enemies to see if outside screen/range, if so make dead
void EnemyManager::deathCheck()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			if (enemies[i].getPosition().x < -100.f)
			{
				enemies[i].setAlive(false);
			}
			if (enemies[i].getPosition().x > 1600.f)
			{
				enemies[i].setAlive(false);
			}
			if (enemies[i].getPosition().y < -100.f)
			{
				enemies[i].setAlive(false);
			}
			if (enemies[i].getPosition().y > 1200.f)
			{
				enemies[i].setAlive(false);
			}
		}
	}
}

//Render all alive enemies
void EnemyManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].isAlive())
		{
			window->draw(enemies[i]);
		}
	}
}

void EnemyManager::getPlayer(Player* play)
{
	player = play;
}

void EnemyManager::reset()
{
	for (int i = 0; i < 20; i++)
	{
		enemies[i].setAlive(false);
		enemies[i].setMoving(false);
		enemies[i].setPosition(spawnPoint);
		enemies[i].setRotation(0.f);
	}
}