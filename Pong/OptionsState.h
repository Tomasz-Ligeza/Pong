#pragma once
#include "State.h"
class OptionsState :
	public State
{
private:


	void initializeMusic();
protected:

public:
	OptionsState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music);

	//functions
	void endState();
	void pollEvents();
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

