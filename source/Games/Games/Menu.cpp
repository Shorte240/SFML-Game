#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::MENU;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Button and Logo setup
	texture.loadFromFile("gfx/Title.png");
	logo.setTexture(&texture);
	logo.setPosition(80.f, 76.f);
	logo.setSize(sf::Vector2f(640.f, 224.f));

	texture2.loadFromFile("gfx/playButton.png");
	playButtonImage.setTexture(&texture2);
	playButtonImage.setPosition(328.f, 300.f);
	playButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	texture3.loadFromFile("gfx/controlsButton.png");
	controlsButtonImage.setTexture(&texture3);
	controlsButtonImage.setPosition(328.f, 348.f);
	controlsButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	texture4.loadFromFile("gfx/objectiveButton.png");
	objectiveButtonImage.setTexture(&texture4);
	objectiveButtonImage.setPosition(328.f, 396.f);
	objectiveButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	texture5.loadFromFile("gfx/quitButton.png");
	quitButtonImage.setTexture(&texture5);
	quitButtonImage.setPosition(328.f, 444.f);
	quitButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);

	//Audio
	audioMgr.addMusic("sfx/menu.ogg", "menu");
	audioMgr.setMusicVolumebyName("menu", 15.f);
	audioMgr.addMusic("sfx/menu2.ogg", "menu2");
	audioMgr.setMusicVolumebyName("menu2", 15.f);
}

Menu::~Menu()
{
}

GameState Menu::getState()
{
	return state;
}

void Menu::update(float dt)
{
	//Randomise to choose between two music files
	randy = rand() % 2;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	if (!hasStarted)
	{
		//Play certain music file based on randy variable
		if (randy == 1)
		{
			audioMgr.playMusicbyName("menu");
			hasStarted = true;
		}
		else
		{
			audioMgr.playMusicbyName("menu2");
			hasStarted = true;
		}
		
	}

	//Update bounding boxes.
	cursor.update(dt);
	playButtonImage.update(dt);
	controlsButtonImage.update(dt);
	objectiveButtonImage.update(dt);
	quitButtonImage.update(dt);

	//To allow music to play when returning to Menu.
	if (state == GameState::LEVEL)
	{
		hasStarted = false;
	}
}

void Menu::handleInput(float dt)
{
	//Check for collision between mouse cursor image and button and mouse click
	if (checkCollision(&cursor, &playButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		audioMgr.stopAllMusic();
		state = GameState::LEVEL;
	}
	else if (checkCollision(&cursor, &controlsButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::CONTROLS;
	}
	else if (checkCollision(&cursor, &objectiveButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::OBJECTIVE;
	}
	else if (checkCollision(&cursor, &quitButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		window->close();
	}
	else
	{
		state = GameState::MENU;
	}

	//Audio
	//Stop all music
	if (input->isKeyDown(sf::Keyboard::BackSpace))
	{
		input->setKeyUp(sf::Keyboard::BackSpace);
		audioMgr.stopAllMusic();
	}
	//Pause playing music
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		audioMgr.pauseAllMusic();
	}
}

void Menu::render()
{
	beginDraw();

	window->setView(*view);
	window->setMouseCursorVisible(false);
	window->draw(logo);
	window->draw(playButtonImage);
	window->draw(controlsButtonImage);
	window->draw(objectiveButtonImage);
	window->draw(quitButtonImage);
	window->draw(cursor);

	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Menu::endDraw()
{
	window->display();
}

bool Menu::checkCollision(Sprites* s1, Sprites* s2)
{
	if (s1->getAABB().left + s1->getAABB().width < s2->getAABB().left)
	{
		return false;
	}
	if (s1->getAABB().left > s2->getAABB().left + s2->getAABB().width)
	{
		return false;
	}
	if (s1->getAABB().top + s1->getAABB().height < s2->getAABB().top)
	{
		return false;
	}
	if (s1->getAABB().top > s2->getAABB().top + s2->getAABB().height)
	{
		return false;
	}

	return true;
}