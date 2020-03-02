#pragma once

#include "State.h"
#include "Bouncer.h"
#include "Ball.h"

using namespace sf;

class GameState :
	public State
{
private:
	//Variables
	Bouncer player;
	Bouncer computer;
	Ball ball;
	Vector2f ballDirection;

	void movePlayer();
	void moveComputer();
	void ballCollide();


public:
	GameState(RenderWindow* window, Event* event, std::stack<State*>* states);
	virtual ~GameState();
	void endState();
	void pollEvents();

	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

