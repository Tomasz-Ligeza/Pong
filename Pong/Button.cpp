#include "Button.h"

#include <iostream>

using namespace sf;

void Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(this->rectangle);
	target.draw(this->text);
}

void Button::isMouseOver(Vector2i mousePos)
{
	if (rectangle.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		rectangle.setFillColor(hoverColor);
	}
	else
		rectangle.setFillColor(normalColor);
}

void Button::isClicked(Vector2i mousePos)
{
	if (rectangle.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		if (onClick != nullptr)
			onClick();
		else
			throw "ON_CLICK_FUNCTION_NOT_INITIALIZED";
	}
}

void Button::setFillColor(Color fillColor)
{
	this->rectangle.setFillColor(fillColor);
	this->normalColor = fillColor;
}

void Button::setHoverColor(Color hoverColor)
{
	this->hoverColor = hoverColor;
}

void Button::setOnClickFunction(std::function<void()> function)
{
	this->onClick = function;
}

Button::Button(Vector2f position, Vector2f size,
	std::string text, Font* font)
{
	this->rectangle.setPosition(position);
	this->rectangle.setSize(size);

	this->text.setString(text);
	this->text.setFont(*font);
	this->text.setCharacterSize(18);
	this->text.setPosition(position.x + size.x / 2.f - this->text.getLocalBounds().width / 2.f,
		position.y + size.y / 2.f - this->text.getGlobalBounds().height / 2.f - this->text.getCharacterSize() / 3.f);
}

Button::~Button()
{
}
