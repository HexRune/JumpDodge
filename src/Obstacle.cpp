#include "Obstacle.h"

void Obstacle::Init(Rectangle rect, Color color, float speed)
{
    this->rect = rect;
    this->color = color;
    this->speed = speed;
    this->scored = false;
}

void Obstacle::Update(float deltaTime)
{
    rect.x -= speed * deltaTime; // 向左移动
}

void Obstacle::Draw()
{
    DrawRectangleRec(rect, color);
}

Rectangle Obstacle::GetRect() const
{
    return rect;
}

bool Obstacle::IsOutOfScreen() const
{
    return rect.x + rect.width < 0; // 完全离开屏幕左侧
}

bool Obstacle::IsScored()
{
    return scored;
}

void Obstacle::MarkAsScored()
{
    scored = true;
}

void Obstacle::Reset()
{
    float x = GetScreenWidth();
    float y = GetRandomValue(420,550);
    rect = Rectangle{x,y,30,GetScreenHeight() - y};
    scored = false;
    speed = GetRandomValue(200,500);
}

int Obstacle::GetRightX() const
{
    return static_cast<int>(rect.x + rect.width);
}
