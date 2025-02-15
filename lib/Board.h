#include "Settings.h"
#include "Ball.h"
#include "Brick.h"

class Board
{
    public:
        Board();
        ~Board();
        void DrawBoard();
        void UpdateBoard(Ball& b);
    private:
        Brick& GetBrick(int x, int y) const;
        Brick* bricks;
};