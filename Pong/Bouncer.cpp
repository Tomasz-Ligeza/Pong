#include "Bouncer.h"

Bouncer::Bouncer()
{
	speed = 0.f;
}

Bouncer::Bouncer(Vector2f pos, Vector2f size, Color color, float speed)
{
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setFillColor(color);
	this->speed = speed;
}

Bouncer::~Bouncer()
{
}

void Bouncer::setPosition(Vector2f pos)
{
	rect.setPosition(pos);
}

Vector2f Bouncer::getPosition()
{
	return rect.getPosition();
}

Vector2f Bouncer::getSize()
{
	return rect.getSize();
}

void Bouncer::move(Vector2f moveVector)
{
	rect.move(moveVector * speed);
}

void Bouncer::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(rect, states);
}
