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
	//Bouncer playersBouncer;
	//Bouncer computersBouncer;

	//Ball ball;


	CircleShape* ball;
	RectangleShape* bouncers[2];
	Font* font;
	Text* timeElapsedText;
	Text* score;
	std::set<Drawable*> drawables;


	bool isActive = true;		///probably have to change it later
	std::string scoreString;
	float timeElapsed;

	void updateTimer(const float& deltaTime);
	void movePlayer();
	void moveComputer();
	void ballCollide();


	void initializeBall();
	void initializeBouncers();
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

