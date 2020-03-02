#include "Ball.h"

Ball::Ball()
{
	speed = 0.f;
}

Ball::Ball(Vector2f pos, float radius, Color color, float speed)
{
	circle.setPosition(pos);
	circle.setRadius(radius);
	circle.setFillColor(color);
	this->speed = speed;
}

Ball::~Ball()
{
}

void Ball::setPosition(Vector2f pos)
{
	circle.setPosition(pos);
}

Vector2f Ball::getPosition()
{
	return circle.getPosition();
}

float Ball::getRadius()
{
	return circle.getRadius();
}

void Ball::setSpeed(float speed)
{
	this->speed = speed;
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::move(Vector2f moveVector)
{
	circle.move(moveVector * speed);
}

void Ball::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(circle, states);
}
