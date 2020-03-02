#include "MenuState.h"
#include "Button.h"
#include "GameState.h"
#include "MenuState.h"

#include <iostream>

void MenuState::initializeButtons()
{
	if (!font->loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "load font error\n";
	}

	Button* startButton = new Button({ 450.f, 145.f }, { 200.f, 80.f },
		"START GAME", font);
	
	startButton->setFillColor({255, 69, 0, 90});
	startButton->setHoverColor({ 255, 69, 0, 50 });
	startButton->setOnClickFunction(std::bind(&MenuState::startGameButtonOnClick, this));
	buttons.push_back(startButton);


	Button* optionsButton = new Button({ 100.f, 400.f }, { 200.f, 80.f },
		"OPTIONS", font);

	optionsButton->setFillColor({ 255, 69, 0, 90 });
	optionsButton->setHoverColor({ 255, 69, 0, 50 });
	optionsButton->setOnClickFunction(std::bind(&MenuState::optionsButtonOnClick, this));
	buttons.push_back(optionsButton);
}

void MenuState::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("textures/background.png"))
	{
		std::cout << "couldnt load from file";
	}
	background.setTexture(backgroundTexture);
}

void MenuState::startGameButtonOnClick()
{
	(*states).push(new GameState(window, event, states));
}

void MenuState::optionsButtonOnClick()
{
	std::cout << "optionsButton\n";
}

MenuState::MenuState(RenderWindow* window, Event* event, std::stack<State*>* states, Font* font)
	: State(window, event, states)
{
	this->font = font;
	initializeButtons();
	initializeBackground();
}

MenuState::~MenuState()
{
}

void MenuState::endState()
{
	std::cout << "getting out of menuState\n";
}

void MenuState::pollEvents()
{
	while (this->window->pollEvent(*event))
	{
		switch (this->event->type)
		{
		case Event::KeyPressed:
		{
			if (this->event->key.code == Keyboard::Escape)
				this->quit = true;
		}
		case Event::MouseButtonPressed:
		{
			for (auto btn : buttons)
			{
				btn->isClicked(Mouse::getPosition(*window));
			}
		}
		}
	}
}

void MenuState::update(const float& deltaTime)
{
	this->checkForQuit();
	
	for (auto btn : buttons)
	{
		btn->isMouseOver(Mouse::getPosition(*window));
	}
}

void MenuState::render(sf::RenderTarget* target)
{
	window->clear(Color::Black);
	window->draw(background);
	//draw smth
	for (auto btn : buttons)
	{
		window->draw(*btn);
	}
}

