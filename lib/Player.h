#include "Vec2.h"
#include "Settings.h"
#include "Ball.h"

class Player
{
public:
    Player() = default;
    Player(Vec2 pos);
    void Draw() const;
    void Update(Ball& ball);
public:
    Vec2 pos;
};