#include "Controls.h"

Controls::Controls(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::CONTROLS;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Image setup
	texture.loadFromFile("gfx/Controls.png");
	controlsImage.setTexture(&texture);
	controlsImage.setPosition(176.f, 100.f);
	controlsImage.setSize(sf::Vector2f(448.f, 128.f));

	texture2.loadFromFile("gfx/backButton.png");
	backButtonImage.setTexture(&texture2);
	backButtonImage.setPosition(328.f, 300.f);
	backButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);
}

Controls::~Controls()
{
}

GameState Controls::getState()
{
	return state;
}

void Controls::handleInput(float dt)
{
	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Update bounding boxes.
	cursor.update(dt);
	backButtonImage.update(dt);

	//Check for collision between cursor and button and if mouse was clicked
	if (checkCollision(&cursor, &backButtonImage) && input->isMouseLeftDown())
	{
		input->setMouseLeftDown(false);
		state = GameState::MENU;
	}
	else
	{
		state = GameState::CONTROLS;
	}
}

void Controls::render()
{
	beginDraw();

	window->setView(*view);
	window->draw(controlsImage);
	window->draw(backButtonImage);
	window->draw(cursor);

	endDraw();
}

void Controls::beginDraw()
{
	window->clear(sf::Color::Blue);
}

void Controls::endDraw()
{
	window->display();
}

bool Controls::checkCollision(Sprites* s1, Sprites* s2)
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
