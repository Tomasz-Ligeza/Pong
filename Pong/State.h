#pragma once

#include <SFML/Graphics.hpp>


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

	bool quit;

	virtual void checkForQuit();

public:
	State(RenderWindow* window, Event* event, std::stack<State*>* states);
	virtual ~State();
	virtual void endState() = 0;
	virtual void pollEvents() = 0;

	const bool& getQuit() const;
	
	//functions
	virtual void update(const float& deltaTime) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};