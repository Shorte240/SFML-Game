#include "Game2.h"

Game2::Game2(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::LEVEL2;
	previousState = GameState::LEVEL2;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Set views centre
	view->setCenter(player.getPosition());

	//HUD Rect Setup
	rect.setSize(sf::Vector2f(290.f, 140.f));
	rect.setPosition(5.f, 855.f);
	rect.setFillColor(sf::Color(255, 255, 255, 100));
	rect.setOutlineColor(sf::Color(0, 0, 0, 100));
	rect.setOutlineThickness(5.f);

	//Give input to classes
	player.getInput(input);
	cursor.getInput(input);

	//Give other classes other classes
	bulletManager.getCursor(&cursor);
	bulletManager.getPlayer(&player);
	enemyManager.getPlayer(&player);

	// Declare and load a font
	font.loadFromFile("font/arial.ttf");

	// Health Text
	healthText.setFont(font);
	healthText.setCharacterSize(30);
	healthText.setStyle(sf::Text::Regular);
	healthText.setFillColor(sf::Color::Red);
	healthText.setPosition(5.f, 855.f);

	// Bullets text
	bulletsText.setFont(font);
	bulletsText.setCharacterSize(30);
	bulletsText.setStyle(sf::Text::Regular);
	bulletsText.setFillColor(sf::Color::Red);
	bulletsText.setPosition(5.f, 885.f);

	// Clips text
	clipsText.setFont(font);
	clipsText.setCharacterSize(30);
	clipsText.setStyle(sf::Text::Regular);
	clipsText.setFillColor(sf::Color::Red);
	clipsText.setPosition(5.f, 915.f);

	// Zombies Killed text
	zombiesKilledText.setFont(font);
	zombiesKilledText.setCharacterSize(30);
	zombiesKilledText.setStyle(sf::Text::Regular);
	zombiesKilledText.setFillColor(sf::Color::Red);
	zombiesKilledText.setPosition(5.f, 945.f);

	//Map tileset setup
	level.loadTexture("gfx/TileSet.png");

	Tile tile;
	std::vector<Tile> tiles;

	for (int i = 0; i < 5; i++)
	{
		tile.setSize(sf::Vector2f(40.f, 40.f));
		tile.setAlive(false);
		tiles.push_back(tile);
	}
	tiles[0].setAlive(true);
	tiles[0].setTextureRect(sf::IntRect(0, 0, 4, 4)); // Black/Wall tile
	tiles[1].setTextureRect(sf::IntRect(4, 0, 4, 4)); // Green/Grass tile
	tiles[2].setTextureRect(sf::IntRect(8, 0, 4, 4)); // Grey/Concrete tile
	tiles[3].setTextureRect(sf::IntRect(0, 4, 4, 4)); // Red/Spawn tile
	tiles[4].setAlive(true);
	tiles[4].setTextureRect(sf::IntRect(4, 4, 4, 4)); // Yellow/Goal tile

	level.setTileSet(tiles);

	//Map dimensions
	sf::Vector2u mapSize(40.f, 30.f);

	//Build map
	std::vector<int> map = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 2, 4, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 0,
		0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 3, 2, 2, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	level.setTileMap(map, mapSize);
	level.setPosition(sf::Vector2f(0.f, 0.f));
	level.buildLevel();

	//Audio Setup
	audioMgr.addMusic("sfx/game2.ogg", "game2");
	audioMgr.setMusicVolumebyName("game2", 15.f);
	audioMgr.addSound("sfx/gun2.ogg", "gun2");
	audioMgr.addSound("sfx/emptyGun.ogg", "emptyGun");
	audioMgr.addSound("sfx/reload.ogg", "reload");
	audioMgr.addSound("sfx/bulletImpact.ogg", "impact");
	audioMgr.addSound("sfx/zombie2.ogg", "zombie2");
	audioMgr.addSound("sfx/enemyDeath.ogg", "enemyDeath");
}

Game2::~Game2() { }

GameState Game2::getState()
{
	return state;
}

GameState Game2::getPreviousState()
{
	return previousState;
}

void Game2::update(float dt)
{
	if (!hasStarted)
	{
		if (audioMgr.isMusicPaused())
		{
			audioMgr.pauseAllMusic();
			hasStarted = true;
		}
		else
		{
			audioMgr.playMusicbyName("game2");
			hasStarted = true;
		}
	}

	if (player.getPosition().x == 180 && player.getPosition().y == 180)
	{
		player.setPosition(1420, 1020);
	}

	//Parameter for returning to main...

	//Lose
	if (player.getHealth() <= 0)
	{
		state = GameState::LOSE;
		audioMgr.stopAllMusic();
	}
	//Pause
	else if (input->isKeyDown(sf::Keyboard::P))
	{
		input->setKeyUp(sf::Keyboard::P);
		audioMgr.pauseAllMusic();
		state = GameState::PAUSE;
		hasStarted = false;
	}
	//Level
	else
	{
		state = GameState::LEVEL2;
	}

	//View mouse changes
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Update classes
	player.update(dt);
	cursor.update(dt);
	enemyManager.update(dt);
	bulletManager.update(dt);

	//Get things updated
	bulletManager.getPlayer(&player);
	bulletManager.getCursor(&cursor);

	//Update Strings
	healthText.setString("Health: " + to_string(player.getHealth()));
	bulletsText.setString("Bullets: " + to_string(player.getBullets()));
	clipsText.setString("Clips: " + to_string(player.getClips()));
	zombiesKilledText.setString("Zombies Killed: " + to_string(player.getZombiesKilled()));

//////**Collision checks**//////
	//--Player and Enemy--//
	std::vector<Enemy>* enemy = enemyManager.getEnemyVector();
	for (int i = 0; i < (int)enemy->size(); i++)
	{
		//if "alive" check collision
		if ((*enemy)[i].isAlive())
		{
			if (checkSphereBounding(&player, &(*enemy)[i]))
			{
				player.enemyCollisionResponse(&(*enemy)[i]);
			}
		}
	}

	//--Player's bounding circle and enemy
	//So that enemy moves--//
	for (int i = 0; i < (int)enemy->size(); i++)
	{
		//if "alive" check collision
		if ((*enemy)[i].isAlive())
		{
			if (checkLargeSphereBounding(&player, &(*enemy)[i]))
			{
				(*enemy)[i].largeCollisionResponse(&player);
			}
		}
	}

	//World Collisions\\
	//World and Player
	std::vector<Tile>* world = level.getLevel();
	for (int i = 0; i < (int)world->size(); i++)
	{
		//if "alive" check collision
		if ((*world)[i].isAlive())
		{
			if (checkCollision(&player, &(*world)[i]))
			{
				if ((*world)[i].getTextureRect() == sf::IntRect(4, 4, 4, 4)) //If it's the "goal" tile
				{
					if (true)
					{
						//Proceed to next level.
						audioMgr.stopAllMusic();
						state = GameState::WIN;
					}
				}
				else
				{
					player.worldCollisionResponse(&(*world)[i]);
				}
			}
		}
	}

	//World and Bullets
	std::vector<Bullet>* bullet = bulletManager.getBulletVector();
	for (int i = 0; i < (int)world->size(); i++)
	{
		for (int j = 0; j < (int)bullet->size(); j++)
		{
			//if "alive" check collision
			if ((*world)[i].isAlive())
			{
				if ((*bullet)[j].isAlive())
				{
					if (checkCollision(&(*bullet)[j], &(*world)[i]))
					{
						if ((*world)[i].getTextureRect() == sf::IntRect(4, 4, 4, 4)) //If it's the "goal" tile
						{
							//Do nothing
						}
						else
						{
							(*bullet)[j].setAlive(false);
							audioMgr.playSoundbyName("impact");
						}
					}
				}
			}
		}
	}

	//Bullets and Zombies
	for (int i = 0; i < (int)bullet->size(); i++)
	{
		//if "alive" check collision
		if ((*bullet)[i].isAlive())
		{
			for (int j = 0; j < (int)enemy->size(); j++)
			{
				if ((*enemy)[j].isAlive())
				{
					if (checkCollision(&(*enemy)[j], &(*bullet)[i]))
					{
						(*bullet)[i].setAlive(false);
						(*enemy)[j].setAlive(false);
						audioMgr.playSoundbyName("enemyDeath");
						player.setZombiesKilled(player.getZombiesKilled() + 1); //Increase players "Zombies Killed" by one.
						bloodManager.spawn((*enemy)[j].getPosition().x, (*enemy)[j].getPosition().y);
					}
				}
			}
		}
	}

	//Zombies and World
	for (int i = 0; i < (int)enemy->size(); i++)
	{
		//if "alive" check collision
		if ((*enemy)[i].isAlive())
		{
			for (int j = 0; j < (int)world->size(); j++)
			{
				if ((*world)[j].isAlive())
				{
					if (checkCollision(&(*enemy)[i], &(*world)[j]))
					{
						if ((*world)[j].getTextureRect() == sf::IntRect(4, 4, 4, 4)) //If it's the "goal" tile
						{
							//Do nothing
						}
						else
						{
							(*enemy)[i].worldCollisionResponse(&(*world)[j]);
						}

					}
				}
			}
		}
	}

	t += dt;

	//Spawn enemies every 5 seconds
	if (t > 5.f)
	{
		enemyManager.spawn();
		audioMgr.playSoundbyName("zombie2");
		t = 0.f;
	}

	//Round players position due to tile issues occurring without it.
	float x = std::round(player.getPosition().x);
	float y = std::round(player.getPosition().y);

	//Set view centre
	view->setCenter(sf::Vector2f(x, y));
}

void Game2::handleInput(float dt)
{
	//Firing gun
	if (player.getBullets() > 0)
	{
		if (input->isMouseLeftDown())
		{
			input->setMouseLeftDown(false);
			audioMgr.playSoundbyName("gun2");
			bulletManager.spawn();

		}
	}
	//Gun is empty but still firing
	if (player.getBullets() == 0 && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		audioMgr.playSoundbyName("emptyGun");
	}
	//Reloading gun
	if (player.getClips() > 0)
	{
		if (input->isKeyDown(sf::Keyboard::R))
		{
			input->setKeyUp(sf::Keyboard::R);
			audioMgr.playSoundbyName("reload");
			player.setClips(player.getClips() - 1);
			player.setBullets(20);
			if (player.getClips() == 0)
			{
				player.setClips(0);
			}
		}
	}

	//Audio
	//Stop all music
	if (input->isKeyDown(sf::Keyboard::BackSpace))
	{
		input->setKeyUp(sf::Keyboard::BackSpace);
		audioMgr.stopAllMusic();
	}
}

void Game2::render()
{
	beginDraw();

	//View centred on player and its contents
	window->setView(*view);
	window->setMouseCursorVisible(false);
	level.render(window);
	bloodManager.render(window);
	enemyManager.render(window);
	bulletManager.render(window);
	window->draw(player);
	window->draw(cursor);

	//Separate view for HUD and its contents
	window->setView(HUD);
	window->draw(rect);
	window->draw(healthText);
	window->draw(bulletsText);
	window->draw(clipsText);
	window->draw(zombiesKilledText);

	//Reset view to prevent centering issues
	window->setView(*view);

	endDraw();
}

void Game2::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game2::endDraw()
{
	window->display();
}

bool Game2::checkSphereBounding(Sprites* s1, Sprites* s2)
{
	//Get radius and centre of sprites.
	float radius1 = s1->getSize().x / 2.f;
	float radius2 = s2->getSize().x / 2.f;
	float xpos1 = s1->getPosition().x + radius1 - s1->getOrigin().x;
	float xpos2 = s2->getPosition().x + radius2 - s2->getOrigin().x;
	float ypos1 = s1->getPosition().y + radius1 - s1->getOrigin().y;
	float ypos2 = s2->getPosition().y + radius2 - s2->getOrigin().y;

	if (pow(xpos2 - xpos1, 2) + pow(ypos2 - ypos1, 2) < pow(radius1 + radius2, 2))
	{
		return true;
	}
	return false;
}

bool Game2::checkCollision(Sprites* s1, Sprites* s2)
{
	if (s1->getAABB().left + s1->getAABB().width <= s2->getAABB().left)
	{
		return false;
	}
	if (s1->getAABB().left >= s2->getAABB().left + s2->getAABB().width)
	{
		return false;
	}
	if (s1->getAABB().top + s1->getAABB().height <= s2->getAABB().top)
	{
		return false;
	}
	if (s1->getAABB().top >= s2->getAABB().top + s2->getAABB().height)
	{
		return false;
	}

	return true;
}

bool Game2::checkLargeSphereBounding(Sprites* s1, Sprites* s2)
{
	//Get radius and centre of sprites.
	float radius1 = s1->getSize().x * 2;
	float radius2 = s2->getSize().x * 2;
	float xpos1 = s1->getPosition().x + radius1 - s1->getOrigin().x - s1->getOrigin().x - s1->getOrigin().x - s1->getOrigin().x;
	float xpos2 = s2->getPosition().x + radius2 - s2->getOrigin().x - s2->getOrigin().x - s2->getOrigin().x - s2->getOrigin().x;
	float ypos1 = s1->getPosition().y + radius1 - s1->getOrigin().y - s1->getOrigin().y - s1->getOrigin().y - s1->getOrigin().y;
	float ypos2 = s2->getPosition().y + radius2 - s2->getOrigin().y - s2->getOrigin().y - s2->getOrigin().y - s2->getOrigin().y;

	if (pow(xpos2 - xpos1, 2) + pow(ypos2 - ypos1, 2) < pow(radius1 + radius2, 2))
	{
		return true;
	}
	return false;
}

void Game2::reset()
{
	player.reset();
	enemyManager.reset();
	bloodManager.reset();
	bulletManager.reset();
	audioMgr.stopAllMusic();
	hasStarted = false;
}