#include "Game.h"


Game::Game()
    :
    player(Vec2(screenWidth / 2 - playerSize.x / 2, screenHeight - 100.0f)),
    ball(Vec2(screenWidth / 2, 600.0f), ballRadius, ballSpeed, Vec2(0.4f, -0.3f))
{
    InitWindow(screenWidth, screenHeight, "Brick Game");
    SetTargetFPS(FPS);
    gameOver = false;
    pause = false;
}

Game::~Game()
{
    CloseWindow();
}

void Game::Run()
{
    while(!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }
}

void Game::UpdateGame()
{
    if (!gameOver && !pause)
    {
		if (IsKeyDown(KEY_LEFT))
			player.pos.x -= 5.0f;
		if (IsKeyDown(KEY_RIGHT))
			player.pos.x += 5.0f;
		if (IsKeyPressed(KEY_SPACE))
			pause = true;
		ball.Update();
		player.Update(ball);
		board.UpdateBoard(ball);
    }
	else if (pause && IsKeyPressed(KEY_SPACE))
		pause = false;
}

void Game::DrawGame()
{
    BeginDrawing();
    ClearBackground(backGroundColor);
        board.DrawBoard();
        player.Draw();
        ball.Draw();
        DrawText(("x:" + itos(static_cast<int>(ball.pos.x))).c_str(), 10, 10, 20, RED);
        DrawText(("y: " + itos(static_cast<int>(ball.pos.x))).c_str(), 100, 10, 20, RED);
    EndDrawing();
}

std::string Game::itos(int num) const
{
    std::string s = "";
    while (num != 0)
    {
        int digit = num % 10;
        s.insert(s.begin(), digit + '0');
        num /= 10;
    }
    return s;
}