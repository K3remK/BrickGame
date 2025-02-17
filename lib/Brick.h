#include "Settings.h"
#include "Ball.h"

class Brick
{
public:
    Brick() = default;
    Brick(int x, int y, Color baseColor, Color lightColor, Color darkColor);
    void Draw() const;
    void Update(Ball& ball);
public:
    int x, y;
    bool isAlive;
    Vec2 pos;
    Color baseColor, lightColor, darkColor;
};