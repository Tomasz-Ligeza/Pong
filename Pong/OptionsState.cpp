#include "OptionsState.h"

void OptionsState::initializeMusic()
{
	if (!buffer.loadFromFile("sounds/options_st.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
	music->setBuffer(buffer);
	music->setLoop(false);
	music->play();
	if (!nextBuffer.loadFromFile("sounds/options_st.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
}

OptionsState::OptionsState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music)
	: State(window, event, states, music)
{
	initializeMusic();
}

void OptionsState::endState()
{
	std::cout << "quitting optionsState";
}

void OptionsState::pollEvents()
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
		}
	}
}

void OptionsState::update(const float& deltaTime)
{
	this->checkForQuit();
}

void OptionsState::render(sf::RenderTarget* target)
{
	window->clear(Color::Black);

	//draw smth
}
