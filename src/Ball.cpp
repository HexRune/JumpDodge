#include<Ball.h>
#include<cmath>

#define NOMINMAX

void Ball::Init(Vector2 position, float radius, Color color)
{
    this->position = position;
    this->radius = radius;
    this->color = color;
}

void Ball::Update(float deltaTime)
{
    velocity.y += gravity * deltaTime;
    position.y += velocity.y * deltaTime;

    if (position.y + radius >= GetScreenHeight())
    {
        position.y = GetScreenHeight() - radius;
        velocity.y = -velocity.y * friction;
        isJump = false;
    }
    
}

void Ball::GetInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        Jump();
    }
    
}

void Ball::Draw()
{
    DrawCircleV(position,radius,color);
}

void Ball::Jump()
{
    if (isJump) return;

    velocity.y = -850;
    isJump = true;
}

Vector2 Ball::GetPosition()
{
    return position;
}

float Ball::GetRadius()
{
    return radius;
}

int Ball::GetLeftX()
{
    return static_cast<int>(position.x - radius);
}
