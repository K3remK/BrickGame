#include "Brick.h"

Brick::Brick(int x, int y, Color baseColor, Color lightColor, Color darkColor)
    :
    x(x),
    y(y),
    isAlive(true),
    baseColor(baseColor),
    lightColor(lightColor),
    darkColor(darkColor)
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