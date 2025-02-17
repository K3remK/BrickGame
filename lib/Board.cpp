#include "Board.h"
#include <iostream>
#include <random>

Board::Board()
{
    bricks = new Brick[row * column];
	remainingBricks = row * column;
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(0, nBrickColors - 1);
    int idx = column / nBrickColors;
    for(int x = 0; x < column; ++x)
    {
        for(int y = 0; y < row; ++y)
        {
            GetBrick(x, y) = Brick(x, y, baseColors[x / idx], lightColors[x / idx], darkColors[x / idx]);
        }
    }
}

Board::~Board()
{
    delete[] bricks;
}

Brick& Board::GetBrick(int x, int y) const
{
    return bricks[y * column + x];
}

void Board::DrawBoard()
{
    for(int x = 0; x < column; ++x)
    {
        for(int y = 0; y < row; ++y)
        {
            Brick& b = GetBrick(x, y);
            if (b.isAlive) b.Draw();
        }
    }
}

void Board::UpdateBoard(Ball& b)
{
 //   bool topLeft = false, topRight = false, bottomLeft = false, bottomRight = false;
 //   int x1 = static_cast<int>(b.pos.x - ballRadius) / brickSize;
 //   int y1 = static_cast<int>(b.pos.y - ballRadius - topMargin) / brickSize;
 //   if (x1 < column && y1 < row) // top left corner of the ball touched a brick
 //   {
 //       if (GetBrick(x1, y1).isAlive)
	//	{
	//		//std::cout << "x1: " << x1 << " y1: " << y1 << std::endl;
 //           topLeft = true;
 //           GetBrick(x1, y1).isAlive = false;
 //       }
 //   }
	//
	//int x2 = (b.pos.x + ballRadius) / brickSize;
	//int y2 = (b.pos.y - ballRadius - topMargin) / brickSize;
	//if (x2 < column && y2 < row) // top right corner of the ball touched a brick
	//{
	//	if (GetBrick(x2, y2).isAlive)
	//	{
	//		//std::cout << "x2: " << x2 << " y2: " << y2 << std::endl;
	//		topRight = true;
	//		GetBrick(x2, y2).isAlive = false;
	//	}
	//}
	//int x3 = (b.pos.x - ballRadius) / brickSize;
	//int y3 = (b.pos.y + ballRadius - topMargin) / brickSize;
	//if (x3 < column && y3 < row) // bottom left corner of the ball touched a brick
	//{
	//	
	//	if (GetBrick(x3, y3).isAlive)
	//	{
	//		//std::cout << "x3: " << x3 << " y3: " << y3 << std::endl;
	//		bottomLeft = true;
	//		GetBrick(x3, y3).isAlive = false;
	//	}
	//}
	//int x4 = (b.pos.x + ballRadius) / brickSize;
	//int y4 = (b.pos.y + ballRadius - topMargin) / brickSize;
	//if (x4 < column && y4 < row) // bottom right corner of the ball touched a brick
	//{
	//	
	//	if (GetBrick(x4, y4).isAlive)
	//	{
	//		//std::cout << "x4: " << x4 << " y4: " << y4 << std::endl;
	//		bottomRight = true;
	//		GetBrick(x4, y4).isAlive = false;
	//	}
	//}

	//if ((bottomRight && bottomLeft) || (topLeft && topRight))
	//{
	//	//std::cout << "entered top or bottom" << std::endl;
	//	b.direction.y *= -1;
	//	return;
	//}
	//else if ((topLeft && bottomLeft) || (topRight && bottomRight))
	//{
	//	//std::cout << "entered left or right" << std::endl;
	//	b.direction.x *= -1;
	//	return;
	//}
 //   else
 //   {
 //       if (topLeft)
 //       {
 //           Brick& brick = GetBrick(x1, y1);
	//		Vec2 rightBottom = Vec2(brick.x * brickSize + brickSize, brick.y * brickSize + topMargin + brickSize);
	//		Vec2 diff = Vec2(rightBottom.x - b.pos.x - b.direction.x * b.speed * 2 - ballRadius, rightBottom.y - b.pos.y - b.direction.y * b.speed * 2 - ballRadius);
	//		diff.y *= -1;
	//		std::cout << b.pos.x - ballRadius << " " << rightBottom.x << " " << b.pos.x - b.direction.x * b.speed - ballRadius << "\n";
	//		float angle1 = (std::atan(diff.y / diff.x) < 0 ? (PI + std::atan(diff.y / diff.x)) : std::atan(diff.y / diff.x));
	//		float angle2 = (std::atan(b.direction.y * -1 / b.direction.x) < 0 ? (PI + std::atan(b.direction.y * -1 / b.direction.x)) : std::atan(b.direction.y * -1 / b.direction.x));
	//		
	//		

	//		if (b.direction.y > 0)
	//		{
	//			b.pos.x = rightBottom.x + 1 + ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else if (b.direction.x > 0)
	//		{
	//			b.pos.y = rightBottom.y + 1 + ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.x < rightBottom.x)
	//		{
	//			b.pos.y = rightBottom.y + 1 + ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.y < rightBottom.y)
	//		{
	//			b.pos.x = rightBottom.x + 1 + ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else
	//		{
	//			if (angle2 > angle1) // going to hit the right side of the player
	//			{
	//				std::cout << "right hit x1: " << x1 << " y1: " << y1 << " a1:" << angle1 << " a2:" << angle2 << " diff.x:" << diff.x << " diff.y:" <<  diff.y 
	//					<< " b.dir.y:" << b.direction.y << " b.dir.y:" << b.direction.y << std::endl;
	//				b.pos.x = rightBottom.x + 1 + ballRadius;
	//				b.direction.x *= -1;
	//			}
	//			else  // going to hit the bottom of the player
	//			{
	//				std::cout << "bottom hit x1: " << x1 << " y1: " << y1 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.y = rightBottom.y + 1 + ballRadius;
	//				b.direction.y *= -1;
	//			}
	//		}
 //       }
	//	else if (topRight)
	//	{
	//		Brick& brick = GetBrick(x2, y2);
	//		Vec2 leftBottom = Vec2(brick.x * brickSize, topMargin + y2 * brickSize + brickSize);
	//		Vec2 diff = leftBottom - ((b.pos + Vec2(ballRadius, -ballRadius)) - (b.direction * b.speed));
	//		diff.y *= -1;
	//		float angle1 = (std::atan(diff.y / diff.x) < 0 ? (PI + std::atan(diff.y / diff.x)) : std::atan(diff.y / diff.x));
	//		float angle2 = (std::atan(b.direction.y * -1 / b.direction.x) < 0 ? (PI + std::atan(b.direction.y * -1 / b.direction.x)) : std::atan(b.direction.y * -1 / b.direction.x));
	//		
	//		if (b.direction.y > 0)
	//		{
	//			b.pos.x = leftBottom.x - 1 - ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else if (b.direction.x < 0)
	//		{
	//			b.pos.y = leftBottom.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.x > leftBottom.x)
	//		{
	//			b.pos.y = leftBottom.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.y < leftBottom.y)
	//		{
	//			b.pos.x = leftBottom.x - 1 - ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else
	//		{
	//			if (angle2 < angle1) // going to hit the left side of the player
	//			{
	//				std::cout << "left hit x2: " << x2 << " y2: " << y2 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.x = leftBottom.x - 1 - ballRadius;
	//				b.direction.x *= -1;
	//			}
	//			else  // going to hit the bottom of the player
	//			{
	//				std::cout << "bottom hit x2: " << x2 << " y2: " << y2 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.y = leftBottom.y - 1 - ballRadius;
	//				b.direction.y *= -1;
	//			}
	//		}
	//	}
	//	else if (bottomLeft)
	//	{
	//		Brick& brick = GetBrick(x3, y3);
	//		Vec2 rightTop = Vec2(brick.x * brickSize + brickSize, topMargin + y3 * brickSize);
	//		Vec2 diff = rightTop - ((b.pos + Vec2(-ballRadius, ballRadius)) - (b.direction * b.speed));
	//		Vec2 x_axis = Vec2(1.0f, 0.0f);
	//		diff.y *= -1;
	//		float angle1 = (std::atan(diff.y / diff.x) < 0 ? (PI + std::atan(diff.y / diff.x)) : std::atan(diff.y / diff.x));
	//		float angle2 = (std::atan(b.direction.y * -1 / b.direction.x) < 0 ? (PI + std::atan(b.direction.y * -1 / b.direction.x)) : std::atan(b.direction.y * -1 / b.direction.x));
	//		
	//		if (b.direction.y < 0)
	//		{
	//			b.pos.x = rightTop.x + 1 + ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else if(b.direction.x > 0)
	//		{
	//			b.pos.y = rightTop.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if(b.pos.x < rightTop.x)
	//		{
	//			b.pos.y = rightTop.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.y > rightTop.y)
	//		{
	//			b.pos.x = rightTop.x + 1 + ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else
	//		{
	//			if (angle2 > angle1) // going to hit the top of player
	//			{
	//				std::cout << "top hit x3: " << x3 << " y3: " << y3 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.y = rightTop.y - 1 - ballRadius;
	//				b.direction.y *= -1;
	//			}
	//			else // going to hit the right side of the player
	//			{
	//				std::cout << "right hit x3: " << x3 << " y3: " << y3 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.x = rightTop.x + 1 + ballRadius;
	//				b.direction.x *= -1;
	//			}
	//		}
	//	}
	//	else if (bottomRight)
	//	{
	//		Brick& brick = GetBrick(x4, y4);
	//		Vec2 leftTop = Vec2(brick.x * brickSize, brick.y * brickSize + topMargin);
	//		Vec2 diff = leftTop - ((b.pos + Vec2(ballRadius, ballRadius)) - (b.direction * b.speed));
	//		diff.y *= -1;
	//		float angle1 = (std::atan(diff.y / diff.x) < 0 ? (PI + std::atan(diff.y / diff.x)) : std::atan(diff.y / diff.x));
	//		float angle2 = (std::atan(b.direction.y * -1 / b.direction.x) < 0 ? (PI + std::atan(b.direction.y * -1 / b.direction.x)) : std::atan(b.direction.y * -1 / b.direction.x));
	//		
	//		if (b.direction.y < 0)
	//		{
	//			b.pos.x = leftTop.x - 1 - ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else if (b.direction.x < 0)
	//		{
	//			b.pos.y = leftTop.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.x > leftTop.x)
	//		{
	//			b.pos.y = leftTop.y - 1 - ballRadius;
	//			b.direction.y *= -1;
	//		}
	//		else if (b.pos.y > leftTop.y)
	//		{
	//			b.pos.x = leftTop.x - 1 - ballRadius;
	//			b.direction.x *= -1;
	//		}
	//		else
	//		{
	//			if (angle2 > angle1) // going to hit the top of player
	//			{
	//				std::cout << "top hit x4: " <<x4<< " y4: " << y4 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.y = leftTop.y - 1 - ballRadius;
	//				b.direction.y *= -1;
	//			}
	//			else // going to hit the left side of the player
	//			{
	//				std::cout << "left hit x4: " << x4 << " y4: " << y4 << " a1:" << angle1 << " a2:" << angle2 << std::endl;
	//				b.pos.x = leftTop.x - 1 - ballRadius;
	//				b.direction.x *= -1;
	//			}
	//		}
	//	}
 //   }

	for (int x = 0; x < column; ++x)
	{
		for (int y = 0; y < row; ++y)
		{
			Brick& br = GetBrick(x, y);
			bool alive = br.isAlive;
			br.Update(b);
			if (alive != br.isAlive) --remainingBricks;
		}
	}
}
