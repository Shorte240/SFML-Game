#include "Win.h"

Win::Win(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::WIN;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Image setup
	texture.loadFromFile("gfx/Winner.png");
	winImage.setTexture(&texture);
	winImage.setPosition(175.f, 100.f);
	winImage.setSize(sf::Vector2f(450.f, 128.f));

	texture2.loadFromFile("gfx/continueButton.png");
	continueButtonImage.setTexture(&texture2);
	continueButtonImage.setPosition(328.f, 300.f);
	continueButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);

	//Audio setup
	audioMgr.addSound("sfx/victory.ogg", "victory");
}

Win::~Win()
{
}

GameState Win::getState()
{
	return state;
}

void Win::handleInput(float dt)
{
	if (!hasStarted)
	{
		audioMgr.playSoundbyName("victory");
		hasStarted = true;
	}
	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Update bounding boxes.
	cursor.update(dt);
	continueButtonImage.update(dt);

	//Collision check
	if (checkCollision(&cursor, &continueButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::MENU;
		hasStarted = false;
	}	
	else
	{
		state = GameState::WIN;
	}
}

void Win::render()
{
	beginDraw();

	window->setView(*view);
	window->draw(winImage);
	window->draw(continueButtonImage);
	window->draw(cursor);

	endDraw();
}

void Win::beginDraw()
{
	window->clear(sf::Color::Blue);
}

void Win::endDraw()
{
	window->display();
}

bool Win::checkCollision(Sprites* s1, Sprites* s2)
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
