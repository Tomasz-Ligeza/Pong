#pragma once
#include "State.h"

#include "Slider.h"
#include "Button.h"

class OptionsState :
	public State
{
public:
	OptionsState(RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font);

	//functions
	void endState();
	void pollEvents();
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);

protected:
private:
	Texture backgroundTexture;
	Sprite background;
	std::vector<Slider*> sliders;
	Slider* selectedSlider;
	std::vector<Button*> buttons;
	Font* font;
	float* volume;

	void initializeVariables();
	void initializeButtons();
	void initializeSliders();
	void initializeBackground();
	void initializeMusic();

};

