// Lab 1 - Intro to Window
// Games Programming

#include "Game.h"
#include "Game2.h"
#include "Input.h"
#include "Menu.h"
#include "Pause.h"
#include "Controls.h"
#include "Win.h"
#include "Lose.h"
#include "Objective.h"
#include "States.h"

void main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Top Down Shooter");
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f)); //Regular view
	sf::View gameView; //Game specific view centered on the player
	gameView.setSize(sf::Vector2f(800.f, 600.f));
	gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	Input input;
	Game game(&window, &input, &gameView);
	Game2 game2(&window, &input, &gameView);
	Menu menu(&window, &input, &view);
	Pause pause(&window, &input, &view);
	Controls controls(&window, &input, &view);
	Win win(&window, &input, &view);
	Lose lose(&window, &input, &view);
	Objective objective(&window, &input, &view);
	//Set initial state
	GameState state = GameState::MENU;
	GameState previousState = state;

	//For Delta Time
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,	event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				//update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					//update input class
					input.setMouseMiddleDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.setMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					//update input class
					input.setMouseMiddleDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.setMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		if (input.isKeyDown(sf::Keyboard::Escape)) 
		{
			input.setKeyUp(sf::Keyboard::Escape);
			MessageBox(NULL, L"Escape was pressed, exiting...", L"Key press", MB_OK);
			window.close();
		}

		//Calculate delta time. How much time has passed
		//since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		//View
		view.setCenter(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

		//game loop
		//Update/Render object based on current game state
		switch (state)
		{
		case (GameState::MENU) :
			game.reset();
			game2.reset();
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			state = menu.getState();
			break;

		case(GameState::LEVEL):
			game.handleInput(deltaTime);
			game.update(deltaTime);
			game.render();
			state = game.getState();
			previousState = game.getPreviousState();
			pause.setPreviousState(previousState);
			break;

		case(GameState::LEVEL2) :
			game2.handleInput(deltaTime);
			game2.update(deltaTime);
			game2.render();
			state = game2.getState();
			previousState = game2.getPreviousState();
			pause.setPreviousState(previousState);
			break;

		case(GameState::PAUSE) :
			pause.handleInput(deltaTime);
			pause.render();
			state = pause.getState();
			previousState = pause.getState();
			break;

		case(GameState::CONTROLS):
			controls.handleInput(deltaTime);
			controls.render();
			state = controls.getState();
			break;

		case(GameState::WIN):
			win.handleInput(deltaTime);
			win.render();
			state = win.getState();
			break;

		case(GameState::LOSE):
			lose.handleInput(deltaTime);
			lose.render();
			state = lose.getState();
			break;

		case(GameState::OBJECTIVE) :
			objective.handleInput(deltaTime);
			objective.render();
			state = objective.getState();
			break;

		default:
			break;

		}
	}
}