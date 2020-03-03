#pragma once

#include "State.h"
#include "Button.h"

using namespace sf;

class MenuState :
	public State
{
private:
	std::vector<Button*> buttons;
	Texture backgroundTexture;
	Sprite background;
	Font* font;
	
	//private functions
	void initializeButtons();
	void startGameButtonOnClick();
	void optionsButtonOnClick();

	void initializeBackground();
	void initializeMusic();
	void resetMusic();

public:
	MenuState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font);
	virtual ~MenuState(); 
	void endState();
	void pollEvents();

	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

