#pragma once

#include "Settings.h"

class Ball
{
public:
	Ball(const Vec2& pos, float radius, float speed, const Vec2& direction);
	void Draw() const;
	void Update();
public:
	Vec2 pos, direction;
	float speed, radius;
};