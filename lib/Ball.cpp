#include "Ball.h"

Ball::Ball(const Vec2& pos, float radius, float speed, const Vec2& direction)
	:
	pos(pos),
	radius(radius),
	speed(speed),
	direction(direction)
{ }


void Ball::Draw() const
{
	DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), radius, ballColor);
}

void Ball::Update() {
	this->pos += (direction.GetNormalized() * speed);
	if (pos.x - ballRadius < 0.0f)
	{
		pos.x = ballRadius;
		direction.x *= -1;
	}
	else if (pos.x + ballRadius > screenWidth)
	{
		pos.x = screenWidth - ballRadius;
		direction.x *= -1;
	}
	else if (pos.y - ballRadius < 0) 
	{
		pos.y = ballRadius;
		direction.y *= -1;
	}
	else if (pos.y + ballRadius > screenHeight)
	{
		pos.y = screenHeight - ballRadius;
		direction.y *= -1;
	}
}
