#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;

class Button : public Drawable, public Transformable
{
protected:
	RectangleShape rectangle;
	Text text;
	std::function<void()> onClick;

	Color normalColor;
	Color hoverColor;

	void draw(RenderTarget& target, RenderStates states) const;
public:
	//Functions
	void isMouseOver(Vector2i mousePos);
	void isClicked(Vector2i mousePos);
	void setFillColor(Color fillColor);
	void setHoverColor(Color hoverColor);
	void setOnClickFunction(std::function<void()> function);


	//Constructors / Destructors
	Button(Vector2f position, Vector2f size, std::string text, Font* font);
	~Button();
};

