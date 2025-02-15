#include "Player.h"
#include <iostream>

Player::Player(Vec2 pos)
    :
    pos(pos)
    {}

void Player::Draw() const
{
    //DrawRectangle(pos.x, pos.y, playerSize.x, playerSize.y, playerColor);

    int edge = brickSize / 8;
    int x_offset = static_cast<int>(pos.x);
    int y_offset = static_cast<int>(pos.y);
    DrawRectangle(x_offset, y_offset, static_cast<int>(playerSize.x), static_cast<int>(playerSize.y), BLACK);
    DrawRectangle(x_offset + edge, y_offset, static_cast<int>(playerSize.x) - edge, static_cast<int>(playerSize.y) - edge, LIGHTGRAY);
    DrawRectangle(x_offset + edge, y_offset + edge, static_cast<int>(playerSize.x) - edge * 2, static_cast<int>(playerSize.y) - edge * 2, GRAY);
}

void Player::Update(Ball &ball)
{
    if(pos.x < 0.0f) pos.x = 0.0f;
    if(pos.x + playerSize.x > screenWidth) pos.x = screenWidth - playerSize.x;

	if (ball.pos.x < pos.x - ballRadius - 5 || ball.pos.x > pos.x + playerSize.x + 5 || ball.pos.y < pos.y - ballRadius - 5 || ball.pos.y > pos.y + playerSize.y + 5) return;

	std::cout << "entered" << std::endl;

    if (pos.x + playerSize.x > ball.pos.x - ballRadius && pos.x + playerSize.x < ball.pos.x + ballRadius &&
        ((ball.pos.y + ballRadius < pos.y + playerSize.y && ball.pos.y + ballRadius > pos.y)
            || (ball.pos.y - ballRadius > pos.y && ball.pos.y - ballRadius < pos.y + playerSize.y)) && ball.direction.x < 0) // ball is coming from right side
    {
		Vec2 rightBottom = pos + playerSize;
		Vec2 diff = rightBottom - ((ball.pos + Vec2(-ballRadius, -ballRadius)) - (ball.direction * ball.speed));
		Vec2 x_axis = Vec2(0.0f, 1.0f);
		float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
		float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
        if (ball.direction.y < 0) // coming from bottom to top
        {
            if (angle2 > angle1) // going to hit the right side of the player
            {
				ball.pos = Vec2(pos.x + playerSize.x + ballRadius + 1, ball.pos.y);
                ball.direction.x *= -1;
            }
            else  // going to hit the bottom of the player
            {
				ball.pos = Vec2(ball.pos.x, pos.y + playerSize.y + ballRadius + 1);
                ball.direction.y *= -1;
            }
        }
        else  // coming from top to bottom (right top corner of the player)
        {
			Vec2 rightTop = Vec2(pos.x + playerSize.x, pos.y);
			Vec2 diff = rightTop - ((ball.pos + Vec2(-ballRadius, ballRadius)) - (ball.direction * ball.speed));
			Vec2 x_axis = Vec2(0.0f, 1.0f);
			float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
			float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
            if (angle2 > angle1) // going to hit the top of player
            {
				ball.pos = Vec2(ball.pos.x, pos.y - ballRadius - 1);
                ball.direction.y *= -1;
            }
            else // going to hit the right side of the player
            {
				ball.pos = Vec2(pos.x + playerSize.x + ballRadius + 1, ball.pos.y);
                ball.direction.x *= -1;
            }
        }
    }
	else if (pos.x > ball.pos.x - ballRadius && pos.x < ball.pos.x + ballRadius &&
		((ball.pos.y + ballRadius < pos.y + playerSize.y && ball.pos.y + ballRadius > pos.y)
			|| (ball.pos.y - ballRadius > pos.y && ball.pos.y - ballRadius < pos.y + playerSize.y)) && ball.direction.x > 0) // ball is coming from left side
	{
		if (ball.direction.y < 0) // coming from bottom to top
		{
			Vec2 leftBottom = Vec2(pos.x, pos.y + playerSize.y);
			Vec2 diff = leftBottom - ((ball.pos + Vec2(ballRadius, -ballRadius)) - (ball.direction * ball.speed));
			Vec2 x_axis = Vec2(0.0f, 1.0f);
			float angle1 = std::acos((diff.x * x_axis.x + diff.y * x_axis.y) / (diff.GetLength() * x_axis.GetLength()));
			float angle2 = std::acos((ball.direction.x * x_axis.x + ball.direction.y * x_axis.y) / (ball.direction.GetLength() * x_axis.GetLength()));
			if (angle2 > angle1) // going to hit the left side of the player
			{
				ball.pos = Vec2(pos.x - ballRadius - 1, ball.pos.y);
				ball.direction.x *= -1;
			}
			else  // going to hit the bottom of the player
			{
				ball.pos = Vec2(ball.pos.x, pos.y + playerSize.y + ballRadius + 1);
				ball.direction.y *= -1;
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
			}
			else // going to hit the left side of the player
			{
				ball.pos = Vec2(pos.x - ballRadius - 1, ball.pos.y);
				ball.direction.x *= -1;
			}
		}
	}
	else if (ball.pos.y + ballRadius > pos.y && ball.pos.y + ballRadius < pos.y + playerSize.y && ball.pos.y - ballRadius < pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + playerSize.x) // ball gonna hit the top side
	{
		ball.pos = Vec2(ball.pos.x, pos.y - ballRadius - 1);
		ball.direction.y *= -1;
	}
	else if (ball.pos.y - ballRadius < pos.y + playerSize.y && ball.pos.y - ballRadius > pos.y && ball.pos.y + ballRadius > playerSize.y + pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + playerSize.x) // ball gonna hit the bottom
	{
		ball.pos = Vec2(ball.pos.x, playerSize.y + pos.y + ballRadius + 1);
		ball.direction.y *= -1;
	}
}