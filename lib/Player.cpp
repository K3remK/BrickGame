#include "Player.h"
#include <random>
#include <iostream>

Player::Player(Vec2 pos)
    :
    pos(pos),
	pLife(playerLife)
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


	for(int i = 0; i < pLife; ++i)
	{
		DrawRectangle(20 + (10 + brickSize) * i, 20, brickSize, 20, WHITE);
    	DrawRectangle(20 + (10 + brickSize) * i + edge, 20, brickSize - edge, 20 - edge, LIGHTGRAY);
    	DrawRectangle(20 + (10 + brickSize) * i + edge, 20 + edge, brickSize - edge * 2, 20 - edge * 2, GRAY);
	}
}

void Player::Update(Ball &ball)
{
    if(pos.x < 0.0f) pos.x = 0.0f;
    if(pos.x + playerSize.x > screenWidth) pos.x = screenWidth - playerSize.x;

	if(ball.pos.y + ballRadius >= screenHeight) --this->pLife;

	if (ball.pos.x < pos.x - ballRadius - 5 || ball.pos.x > pos.x + playerSize.x + 5 || ball.pos.y < pos.y - ballRadius - 5 || ball.pos.y > pos.y + playerSize.y + 5) return;

	bool hit = false;

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
				hit = true;
            }
            else  // going to hit the bottom of the player
            {
				ball.pos = Vec2(ball.pos.x, pos.y + playerSize.y + ballRadius + 1);
                ball.direction.y *= -1;
				hit = true;
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
				hit = true;
            }
            else // going to hit the right side of the player
            {
				ball.pos = Vec2(pos.x + playerSize.x + ballRadius + 1, ball.pos.y);
                ball.direction.x *= -1;
				hit = true;
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
				hit = true;
			}
			else  // going to hit the bottom of the player
			{
				ball.pos = Vec2(ball.pos.x, pos.y + playerSize.y + ballRadius + 1);
				ball.direction.y *= -1;
				hit = true;
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
				hit = true;
			}
			else // going to hit the left side of the player
			{
				ball.pos = Vec2(pos.x - ballRadius - 1, ball.pos.y);
				ball.direction.x *= -1;
				hit = true;
			}
		}
	}
	else if (ball.pos.y + ballRadius > pos.y && ball.pos.y + ballRadius < pos.y + playerSize.y && ball.pos.y - ballRadius < pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + playerSize.x) // ball gonna hit the top side
	{
		ball.pos = Vec2(ball.pos.x, pos.y - ballRadius - 1);
		ball.direction.y *= -1;
		hit = true;
	}
	else if (ball.pos.y - ballRadius < pos.y + playerSize.y && ball.pos.y - ballRadius > pos.y && ball.pos.y + ballRadius > playerSize.y + pos.y
		&& ball.pos.x > pos.x && ball.pos.x < pos.x + playerSize.x) // ball gonna hit the bottom
	{
		ball.pos = Vec2(ball.pos.x, playerSize.y + pos.y + ballRadius + 1);
		ball.direction.y *= -1;
		hit = true;
	}


	if(hit)
	{
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> distX(0, PI);
		std::uniform_real_distribution<float> distY(-PI / 2, PI / 2);
		ball.direction.x += std::cos(distX(rng));
		ball.direction.y += std::sin(distY(rng));
		ball.direction.Normalize();
	}
}