#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Slider : public Drawable
{
public:
	//constructors
	Slider(Vector2f position, Vector2f size, float* valueAddress = nullptr);
	~Slider();

	void setPosition(Vector2f position);
	void setSize(Vector2f size);
	void setValuePointer(float* value);
	void setRangeOfValues(float min, float max);

	void setColorOfSlider(Color color);
	void setColorOfZipper(Color color);
	bool isMouseOverZipper(Vector2i mousePos);
	void dragZipper(Vector2i mousePos);

protected:
	void draw(RenderTarget& target, RenderStates states) const;

private:
	float* value;
	float minValue, maxValue;

	RectangleShape slider;
	RectangleShape zipper;
	VertexArray* lines;

};

