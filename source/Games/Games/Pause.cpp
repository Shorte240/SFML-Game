#include "Pause.h"

Pause::Pause(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::PAUSE;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Image Setup
	texture.loadFromFile("gfx/Paused.png");
	logo.setTexture(&texture);
	logo.setPosition(160.f, 100.f);
	logo.setSize(sf::Vector2f(480.f, 112.f));

	texture2.loadFromFile("gfx/resumeButton.png");
	resumeButtonImage.setTexture(&texture2);
	resumeButtonImage.setPosition(328.f, 300.f);
	resumeButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	texture3.loadFromFile("gfx/quitButton.png");
	quitButtonImage.setTexture(&texture3);
	quitButtonImage.setPosition(328.f, 348.f);
	quitButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);
}

Pause::~Pause()
{
}

GameState Pause::getState()
{
	return state;
}

GameState Pause::getPreviousState()
{
	return previousState;
}

void Pause::setPreviousState(GameState v)
{
	previousState = v;
}

void Pause::handleInput(float dt)
{
	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Update bounding boxes.
	cursor.update(dt);
	resumeButtonImage.update(dt);
	quitButtonImage.update(dt);

	//Check for collision with Mouse Cursor image and Mouse Click
	if (checkCollision(&cursor, &resumeButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = previousState; //Previous state given by each game/level to allow returning to correct game/level.
	}
	else if (checkCollision(&cursor, &quitButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::MENU;
	}
	else
	{
		state = GameState::PAUSE;
	}
}

void Pause::render()
{
	beginDraw();

	window->setView(*view);
	window->draw(logo);
	window->draw(resumeButtonImage);
	window->draw(quitButtonImage);
	window->draw(cursor);

	endDraw();
}

void Pause::beginDraw()
{
	window->clear(sf::Color::Blue);
}

void Pause::endDraw()
{
	window->display();
}

bool Pause::checkCollision(Sprites* s1, Sprites* s2)
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
