#include "Game.h"

Game::Game()
{
	initializeWindow();
	initializeVariables();
	initializeStates();
	loadFont();
}

void Game::initializeWindow()
{
	window = new RenderWindow(VideoMode(800, 600), "Window");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
}

void Game::initializeVariables()
{
	event = new Event();
	font = new Font();
}

void Game::initializeStates()
{
	this->states.push(new MenuState(window, event, &states, font));
}

void Game::loadFont()
{
	//font->loadFromFile("fonts\\arial.ttf");
}

Game::~Game()
{
	delete this->window;
	while (!states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::update()
{
	if (!this->states.empty())
	{
		//polling sfml events
		this->states.top()->pollEvents();
		this->states.top()->update(this->deltaTime);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		window->close();
	}
}

void Game::render()
{
	//clear window
	window->clear(Color::Black);

	//rander items
	if (!this->states.empty())
		this->states.top()->render();

	//display drawn objects
	window->display();
}

void Game::updateDeltaTime()
{
	this->deltaTime = this->clock.restart().asSeconds();
}

void Game::endApplication()
{
	std::cout << "Ending application.\n";
}
