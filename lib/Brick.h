#include "Settings.h"

class Brick
{
public:
    Brick() = default;
    Brick(int x, int y, Color baseColor, Color lightColor, Color darkColor);
    void Draw() const;
public:
    int x, y;
    bool isAlive;
    Color baseColor, lightColor, darkColor;
};