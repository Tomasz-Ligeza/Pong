#include "MenuState.h"
#include "Button.h"
#include "GameState.h"
#include "MenuState.h"
#include "OptionsState.h"

#include <iostream>

void MenuState::initializeButtons()
{
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

void MenuState::startGameButtonOnClick()
{
	(*states).push(new GameState(window, event, states, music));
}

void MenuState::optionsButtonOnClick()
{
	(*states).push(new OptionsState(window, event, states, music, font));
}

void MenuState::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("textures/background.png"))
	{
		std::cout << "couldnt load from file";
	}
	background.setTexture(backgroundTexture);
}

void MenuState::initializeMusic()
{
	if (!buffer.loadFromFile("sounds/start.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
	music->setBuffer(buffer);
	music->setLoop(false);
	music->play();
	if (!nextBuffer.loadFromFile("sounds/menu_st.wav"))
	{
		std::cout << "couldnt load sound\n";
	}
}

void MenuState::resetMusic()
{
	if (music->getStatus() == SoundSource::Status::Stopped)
	{
		music->setBuffer(nextBuffer);
		music->setLoop(true);
		music->play();
	}
}

MenuState::MenuState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font)
	: State(window, event, states, music)
{
	this->font = font;
	initializeButtons();
	initializeBackground();
	initializeMusic();
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
		case Event::Closed:
		{
			this->window->close();
			break;
		}
		case Event::KeyPressed:
		{
			if (this->event->key.code == Keyboard::Escape)
				this->quit = true;
			break;
		}
		case Event::MouseButtonPressed:
		{
			for (auto &btn : buttons)
			{
				btn->isClicked(Mouse::getPosition(*window));
			}
			break;
		}
		}
	}
}

void MenuState::update(const float& deltaTime)
{
	this->checkForQuit();
	this->resetMusic();
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

