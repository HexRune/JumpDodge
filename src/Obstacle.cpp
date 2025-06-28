#include<Obstacle.h>

void Obstacle::Init(Rectangle rect, Color color, float speed)
{
    this->rect = rect;
    this->color = color;
    this->speed = speed;
    this->scored = false;
}

void Obstacle::Update(float deltaTime)
{
    rect.x -= speed * deltaTime;
}

void Obstacle::Draw()
{
    DrawRectangleRec(rect, color);
}

bool Obstacle::IsOutOfScreen() const
{
    return rect.x + rect.width < 0;
}

int Obstacle::GetRightX() const
{
    return static_cast<int>(rect.x + rect.width);
}

bool Obstacle::IsScored()
{
    return scored;
}

void Obstacle::Reset()
{
    float x = GetScreenWidth();
    float y = GetRandomValue(420,550);
    rect = Rectangle{x,y,30,GetScreenHeight() - y};
    scored = false;
    speed = GetRandomValue(200,500);
}

void Obstacle::ScoreIsAdd()
{
    scored = true;
}

Rectangle Obstacle::GetRect()
{
    return rect;
}
