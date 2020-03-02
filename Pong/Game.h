#pragma once

#include "GameState.h"
#include "MenuState.h"
#include <iostream>

using namespace sf;

class Game
{
private:
	//Variables
	RenderWindow* window;
	Event* event;
	Font* font;

	Clock clock;
	float deltaTime;

	std::stack<State*> states;

	//intitialization
	void initializeWindow();
	void initializeVariables();
	void initializeStates();
	void loadFont();

	//priv functions
	void updateDeltaTime();
	void endApplication();
public:
	//Ctors / Dtors
	Game();
	virtual ~Game();

	//Functions
	void run();
	void update();
	void render();
};