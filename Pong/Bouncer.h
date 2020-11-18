#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bouncer : public Drawable, public Transformable
{
private:

protected:
	RectangleShape rect;
	float speed;

public:
	Bouncer();
	Bouncer(Vector2f pos, Vector2f size, Color color, float speed);
	~Bouncer();

	void setPosition(Vector2f pos);
	Vector2f getPosition();
	Vector2f getSize();

	void move(Vector2f moveVector);
	void draw(RenderTarget& target, RenderStates states) const;
};

