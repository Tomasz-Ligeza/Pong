#include "Slider.h"
#include <iostream>
Slider::Slider(Vector2f position, Vector2f size, float* valueAddress)
{
	lines = new VertexArray(sf::LinesStrip, 2);
	setSize(size);
	setPosition(position);
	setRangeOfValues(0.f, 100.f);
	value = valueAddress;

	setColorOfSlider(Color(200, 200, 200));
	setColorOfZipper(Color(50, 50, 50));
	(*lines)[0].color = Color(255, 255, 255, 50);
	(*lines)[1].color = Color(255, 255, 255, 75);
}

Slider::~Slider()
{
	delete lines;
}

void Slider::setPosition(Vector2f position)
{
	slider.setPosition(position);
	zipper.setPosition(position + slider.getSize() * 0.5f);

	(*lines)[0].position = Vector2f(slider.getPosition().x + slider.getSize().x * 0.05f, slider.getPosition().y + slider.getSize().y / 2.f);
	(*lines)[1].position = Vector2f(slider.getPosition().x + slider.getSize().x * 0.95f, slider.getPosition().y + slider.getSize().y / 2.f);
}

void Slider::setSize(Vector2f size)
{
	slider.setSize(size);
	zipper.setSize(Vector2f(size.x * 0.1f, size.y * 0.8f));
	zipper.setOrigin(Vector2f(zipper.getSize() * 0.5f));
}

void Slider::setValuePointer(float* value)
{
	this->value = value;
}

void Slider::setRangeOfValues(float min, float max)
{
	minValue = min;
	maxValue = max;
}

void Slider::setColorOfSlider(Color color)
{
	slider.setFillColor(color);
}

void Slider::setColorOfZipper(Color color)
{
	zipper.setFillColor(color);
}

bool Slider::isMouseOverZipper(Vector2i mousePos)
{
	if (zipper.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		return true;
	return false;
}

void Slider::dragZipper(Vector2i mousePos)
{
	if (mousePos.x - zipper.getSize().x * 0.5f >= slider.getPosition().x &&
		mousePos.x + zipper.getSize().x * 0.5f <= slider.getPosition().x + slider.getSize().x)
	{
		zipper.setPosition(static_cast<float>(mousePos.x), zipper.getPosition().y);
		*value = ((zipper.getPosition().x - zipper.getSize().x * 0.5f - slider.getPosition().x) / (slider.getSize().x - zipper.getSize().x)) * (maxValue - minValue) + minValue;
	}
}

void Slider::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(slider, states);
	target.draw(*lines, states);
	target.draw(zipper, states);
}
