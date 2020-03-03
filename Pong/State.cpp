#include "State.h"

State::State(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music)
{
	this->window = window;
	this->event = event;
	this->states = states;
	this->music = music;
	this->quit = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (event->type == Event::KeyPressed)
	{
		if (event->key.code == Keyboard::Escape)
			this->quit = true;
	}
}


