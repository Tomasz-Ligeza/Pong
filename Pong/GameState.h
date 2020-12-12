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
	Bouncer playersBouncer;
	Bouncer computersBouncer;
	Ball ball;
	Vector2f ballDirection;
	Font* font;
	Text* timeElapsedText;
	Text* score;
	std::vector<Drawable*> drawables;


	bool isActive = true;		///probably have to change it later
	float timeElapsed;

	void updateTimer(const float& deltaTime);
	void movePlayer();
	void moveComputer();
	void ballCollide();

	void initializeMusic();
	void initializeText();
	void initializeBouncersPosition();
	void resetMusic();

public:
	GameState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font);
	virtual ~GameState();
	void endState();
	void pollEvents();

	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

