#include "Settings.h"
#include "Board.h"
#include "Player.h"
#include <string>

class Game
{
    public:
        Game();
        ~Game();
        void Run();
    private:
    // Private class functions
        void DrawGame();
        void UpdateGame();
        std::string itos(int num) const;
    private:
    // private class members
        Board board;
        Ball ball;
        Player player;
        bool gameOver;
        bool pause;
};