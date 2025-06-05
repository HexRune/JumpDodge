#pragma once
#include "Ball.h"
#include "Obstacle.h"

class Game
{
private:
    /* data */
    Ball ball;
    Obstacle obstacle;
    int score;
    bool gameOver;
public:
    Game() = default;
    ~Game() = default;

    void Init();
    void GetInput();
    void Update(float deltaTime);
    void Draw();
    void Reset();

    void Run();
};
