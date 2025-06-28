#pragma once
#include <raylib.h>

class Obstacle
{
private:
    Rectangle rect;
    Color color;
    float speed;
    bool scored;
    
public:
    Obstacle() = default;
    ~Obstacle() = default;

    void Init(Rectangle rect,Color color,float speed);
    void Update(float deltaTime);
    void Draw();
    bool IsOutOfScreen() const;
    int GetRightX() const;
    bool IsScored();
    void Reset();
    void ScoreIsAdd();

    Rectangle GetRect();
};

