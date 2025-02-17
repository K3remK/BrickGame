#include "Game.h"
#include <iostream>

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
    if (player.pLife <= 0) gameOver = true;
    if (!gameOver && !pause)
    {
		if (IsKeyDown(KEY_LEFT))
			player.pos.x -= ball.speed;
		if (IsKeyDown(KEY_RIGHT))
			player.pos.x += ball.speed;
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

        if (gameOver) {
            DrawText("Game Over!", screenWidth / 2 - 50, screenHeight / 2, 20, RED);
            DrawText(("Remaining Bricks: " + itos(board.remainingBricks)).c_str(), screenWidth / 2 - 80, screenHeight / 2 + 20, 20, RED);
        }
        if (pause) DrawText("Paused!", screenWidth / 2 - 50, screenHeight / 2, 20, RED);

        //DrawText(("x:" + itos(static_cast<int>(ball.pos.x))).c_str(), 10, 10, 20, RED);
        //DrawText(("y: " + itos(static_cast<int>(ball.pos.y))).c_str(), 100, 10, 20, RED);
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