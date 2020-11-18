#include "OptionsState.h"

void OptionsState::initializeVariables()
{
	volume = new float(music->getVolume());
}

void OptionsState::initializeButtons()
{
	//initialize buttons
}

void OptionsState::initializeSliders()
{
	selectedSlider = nullptr;
	//initialize sliders
	Slider* volumeSlider = new Slider(Vector2f(350.f, 180.f), Vector2f(300.f, 60.f), volume);
	sliders.push_back(volumeSlider);
}

void OptionsState::initializeBackground()
{
	if (!backgroundTexture.loadFromFile("textures/backgroundOptions.png"))
	{
		std::cout << "couldnt load from file";
	}
	background.setTexture(backgroundTexture);
}

void OptionsState::initializeMusic()
{
	if (!buffer.loadFromFile("sounds/options_st.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
	music->setBuffer(buffer);
	music->setLoop(true);
	music->play();
	if (!nextBuffer.loadFromFile("sounds/options_st.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
}

OptionsState::OptionsState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font)
	: State(window, event, states, music)
{
	this->font = font;

	initializeVariables();
	initializeButtons();
	initializeSliders();
	initializeBackground();
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
		case Event::MouseButtonPressed:
		{
			if (event->mouseButton.button == Mouse::Button::Left)
			{
				for (auto& btn : buttons)
				{
					btn->isClicked(Mouse::getPosition(*window));
				}
				for (auto& sld : sliders)
				{
					if(sld->isMouseOverZipper(Mouse::getPosition(*window)))
					{
						selectedSlider = sld;
					}
				}
				break;
			}
		}
		case Event::MouseButtonReleased:
		{
			if (event->mouseButton.button == Mouse::Button::Left)
			{
				selectedSlider = nullptr;
			}
		}
		}
	}
}

void OptionsState::update(const float& deltaTime)
{
	this->checkForQuit();
	if (selectedSlider != nullptr)
	{
		selectedSlider->dragZipper(Mouse::getPosition(*window));
		music->setVolume(*volume);
	}
}

void OptionsState::render(sf::RenderTarget* target)
{
	window->clear(Color::Black);

	//draw smth
	window->draw(background);
	for (auto &btn : buttons)
	{
		window->draw(*btn);
	}
	for (auto& sld : sliders)
	{
		window->draw(*sld);
	}
}
