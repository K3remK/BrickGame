#include "Brick.h"

Brick::Brick(int x, int y, Color baseColor, Color lightColor, Color darkColor)
    :
    x(x),
    y(y),
    isAlive(true),
    baseColor(baseColor),
    lightColor(lightColor),
    darkColor(darkColor),
	pos(Vec2(x * brickSize, y * brickSize + topMargin))
    {}

void Brick::Draw() const
{
    int edge = brickSize / 8;
    int x_offset = x * brickSize;
    int y_offset = y * brickSize + topMargin;
    DrawRectangle(x_offset, y_offset, brickSize, brickSize, darkColor);
    DrawRectangle(x_offset + edge, y_offset, brickSize - edge, brickSize - edge, lightColor);
    DrawRectangle(x_offset + edge, y_offset + edge, brickSize - edge * 2, brickSize - edge * 2, baseColor);
}

void Brick::Update(Ball& ball)
{
	if (!isAlive) return;
	if (pos.x + brickSize > ball.pos.x - ballRadius && pos.x + brickSize < ball.pos.x + ballRadius &&
		((ball.pos.y + ballRadius < pos.y + brickSize && ball.pos.y + ballRadius > pos.y)
			|| (ball.pos.y - ballRadius > pos.y && ball.pos.y - ballRadius < pos.y + brickSize)) && ball.direction.x < 0) // ball is coming from right side
	{
		Vec2 rightBottom = pos + Vec2(brickSize, brickSize);
		Vec2 diff = rightBottom - ((ball.pos + Vec2(-ballRadius, -ballRadius)) - (ball.direction * ball.speed));
		Vec2 x_axis = Vec2(0.0f, 1.0f);
		float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
		float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
		if (ball.direction.y < 0) // coming from bottom to top
		{
			if (angle2 > angle1) // going to hit the right side of the player
			{
				ball.pos = Vec2(pos.x + brickSize + ballRadius + 1, ball.pos.y);
				ball.direction.x *= -1;
				isAlive = false;
				return;
			}
			else  // going to hit the bottom of the player
			{
				ball.pos = Vec2(ball.pos.x, pos.y + brickSize + ballRadius + 1);
				ball.direction.y *= -1;
				isAlive = false;
				return;
			}
		}
		else  // coming from top to bottom (right top corner of the player)
		{
			Vec2 rightTop = Vec2(pos.x + brickSize, pos.y);
			Vec2 diff = rightTop - ((ball.pos + Vec2(-ballRadius, ballRadius)) - (ball.direction * ball.speed));
			Vec2 x_axis = Vec2(0.0f, 1.0f);
			float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
			float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
			if (angle2 > angle1) // going to hit the top of player
			{
				ball.pos = Vec2(ball.pos.x, pos.y - ballRadius - 1);
				ball.direction.y *= -1;
				isAlive = false;
				return;
			}
			else // going to hit the right side of the player
			{
				ball.pos = Vec2(pos.x + brickSize + ballRadius + 1, ball.pos.y);
				ball.direction.x *= -1;
				isAlive = false;
				return;
			}
		}
	}
	else if (pos.x > ball.pos.x - ballRadius && pos.x < ball.pos.x + ballRadius &&
		((ball.pos.y + ballRadius < pos.y + brickSize && ball.pos.y + ballRadius > pos.y)
			|| (ball.pos.y - ballRadius > pos.y && ball.pos.y - ballRadius < pos.y + brickSize)) && ball.direction.x > 0) // ball is coming from left side
	{
		if (ball.direction.y < 0) // coming from bottom to top
		{
			Vec2 leftBottom = Vec2(pos.x, pos.y + brickSize);
			Vec2 diff = leftBottom - ((ball.pos + Vec2(ballRadius, -ballRadius)) - (ball.direction * ball.speed));
			Vec2 x_axis = Vec2(0.0f, 1.0f);
			float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
			float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
			if (angle2 > angle1) // going to hit the left side of the player
			{
				ball.pos = Vec2(pos.x - ballRadius - 1, ball.pos.y);
				ball.direction.x *= -1;
				isAlive = false;
				return;
			}
			else  // going to hit the bottom of the player
			{
				ball.pos = Vec2(ball.pos.x, pos.y + brickSize + ballRadius + 1);
				ball.direction.y *= -1;
				isAlive = false;
				return;
			}
		}
		else  // coming from top to bottom (left top corner of the player)
		{
			Vec2 leftTop = pos;
			Vec2 diff = leftTop - ((ball.pos + Vec2(ballRadius, ballRadius)) - (ball.direction * ball.speed));
			Vec2 x_axis = Vec2(0.0f, 1.0f);
			float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
			float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
			if (angle2 > angle1) // going to hit the top of player
			{
				ball.pos = Vec2(pos.x, pos.y - ballRadius - 1);
				ball.direction.y *= -1;
				isAlive = false;
				return;
			}
			else // going to hit the left side of the player
			{
				ball.pos = Vec2(pos.x - ballRadius - 1, ball.pos.y);
				ball.direction.x *= -1;
				isAlive = false;
				return;
			}
		}
	}
	else if (ball.pos.y + ballRadius > pos.y && ball.pos.y + ballRadius < pos.y + brickSize && ball.pos.y - ballRadius < pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + brickSize) // ball gonna hit the top side
	{
		ball.pos = Vec2(ball.pos.x, pos.y - ballRadius - 1);
		ball.direction.y *= -1;
		isAlive = false;
		return;
	}
	else if (ball.pos.y - ballRadius < pos.y + brickSize && ball.pos.y - ballRadius > pos.y && ball.pos.y + ballRadius > brickSize + pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + brickSize) // ball gonna hit the bottom
	{
		ball.pos = Vec2(ball.pos.x, brickSize + pos.y + ballRadius + 1);
		ball.direction.y *= -1;
		isAlive = false;
		return;
	}
}
