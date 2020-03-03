#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream> //delete after releasing
#include <stack>
#include <vector>

using namespace sf;

class State
{
private:

protected:
	RenderWindow* window;
	Event* event;
	std::stack<State*>* states;
	Sound* music;
	SoundBuffer buffer;
	SoundBuffer nextBuffer;

	bool quit;
	virtual void checkForQuit();
	virtual void initializeMusic() = 0;

public:
	State(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music);
	virtual ~State();
	virtual void endState() = 0;
	virtual void pollEvents() = 0;

	const bool& getQuit() const;
	
	//functions
	virtual void update(const float& deltaTime) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};