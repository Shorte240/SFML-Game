#include "Lose.h"

Lose::Lose(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::LOSE;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Image setup
	texture.loadFromFile("gfx/Loser.png");
	loseImage.setTexture(&texture);
	loseImage.setPosition(136.f, 100.f);
	loseImage.setSize(sf::Vector2f(528.f, 84.f));

	texture2.loadFromFile("gfx/continueButton.png");
	continueButtonImage.setTexture(&texture2);
	continueButtonImage.setPosition(328.f, 300.f);
	continueButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);

	//Audio setup
	audioMgr.addSound("sfx/defeat.ogg", "defeat");
}

Lose::~Lose()
{
}

GameState Lose::getState()
{
	return state;
}

void Lose::handleInput(float dt)
{
	//Play sound on start
	if (!hasStarted)
	{
		audioMgr.playSoundbyName("defeat");
		hasStarted = true;
	}

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Update bounding boxes.
	cursor.update(dt);
	continueButtonImage.update(dt);

	//Check for collision and mouse click between button and cursor
	if (checkCollision(&cursor, &continueButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::MENU;
		hasStarted = false;
	}
	else
	{
		state = GameState::LOSE;
	}
}

void Lose::render()
{
	beginDraw();

	window->setView(*view);
	window->draw(loseImage);
	window->draw(continueButtonImage);
	window->draw(cursor);

	endDraw();
}

void Lose::beginDraw()
{
	window->clear(sf::Color(204, 0, 0));
}

void Lose::endDraw()
{
	window->display();
}

bool Lose::checkCollision(Sprites* s1, Sprites* s2)
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
