#include "Game.h"
#include <string>

void Game::Init()
{
    InitWindow(900, 600, "JumpDodge");
    SetTargetFPS(60);
    Reset();
}

void Game::Reset()
{
    gameOver = false;
    score = 0;
    ball.Init({200, 300}, 25, RED);
    obstacle.Init({900, 450, 30, 150}, WHITE, 200);
}

void Game::GetInput()
{
    if (gameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            Reset();
        }
        
    }
    else
    {
        ball.GetInput();
    }
}

void Game::Update(float deltaTime)
{
    if (gameOver)
        return;

    ball.Update(deltaTime);
    obstacle.Update(deltaTime);
    if (!obstacle.IsScored() && obstacle.GetRightX() < ball.GetLeftX())
    {
        score++;
        obstacle.MarkAsScored();
    }
    if (obstacle.IsOutOfScreen())
    {
        obstacle.Reset();
    }
    if (ball.CheckCollision(obstacle.GetRect()))
    {
        gameOver = true;
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    obstacle.Draw();
    ball.Draw();

    DrawText(std::to_string(score).c_str(), GetScreenWidth() / 2, 30, 32, WHITE);

    if (gameOver)
    {
        DrawText("GameOver", GetScreenWidth() / 4, GetScreenHeight() / 3, 100, RED);
        DrawText("Press Enter To Restart", GetScreenWidth() / 4+40, GetScreenHeight() / 2, 32, WHITE);
    }

    EndDrawing();
}

void Game::Run()
{
    Init();
    while (!WindowShouldClose())
    {
        GetInput();
        Update(GetFrameTime());
        Draw();
    }
    CloseWindow();
}