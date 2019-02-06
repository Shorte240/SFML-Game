#include "Objective.h"

Objective::Objective(sf::RenderWindow* hwnd, Input* in, sf::View* vi)
{
	window = hwnd;
	input = in;
	state = GameState::OBJECTIVE;
	view = vi;

	//Give input mouse location
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse_world = window->mapPixelToCoords(mouse);
	input->setMouseWorld(&mouse_world);

	//Image setup
	texture.loadFromFile("gfx/objective.png");
	objectiveImage.setTexture(&texture);
	objectiveImage.setPosition(100.f, 100.f);
	objectiveImage.setSize(sf::Vector2f(600.f, 400.f));

	texture2.loadFromFile("gfx/backButton.png");
	backButtonImage.setTexture(&texture2);
	backButtonImage.setPosition(328.f, 500.f);
	backButtonImage.setSize(sf::Vector2f(144.f, 48.f));

	//Give cursor input
	cursor.getInput(input);
}

Objective::~Objective()
{
}

GameState Objective::getState()
{
	return state;
}

void Objective::handleInput(float dt)
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
		state = GameState::OBJECTIVE;
	}
}

void Objective::render()
{
	beginDraw();

	window->setView(*view);
	window->draw(objectiveImage);
	window->draw(backButtonImage);
	window->draw(cursor);

	endDraw();
}

void Objective::beginDraw()
{
	window->clear(sf::Color::Blue);
}

void Objective::endDraw()
{
	window->display();
}

bool Objective::checkCollision(Sprites* s1, Sprites* s2)
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
