#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball : public Drawable, public Transformable
{

private:

protected:
	CircleShape circle;
	float speed;

public:
	Ball();
	Ball(Vector2f pos, float radius, Color color, float speed);
	~Ball();

	void setPosition(Vector2f pos);
	Vector2f getPosition();
	float getRadius();
	void setSpeed(float speed);
	float getSpeed();

	void move(Vector2f moveVector);
	void draw(RenderTarget& target, RenderStates states) const;
};

