#include "Ball.h"
#include <cmath>

void Ball::Init(Vector2 position, int radius, Color color)
{
    this->position = position;
    this->radius = radius;
    this->color = color;
}

// 更新小球位置（物理模拟）
void Ball::Update(float deltaTime)
{
    // 应用重力（速度随时间增加）
    velocity.y += gravity * deltaTime;

    // 更新位置
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // 检测地面碰撞
    if (position.y + radius >= GetScreenHeight())
    {
        position.y = GetScreenHeight() - radius; // 防止穿透地面
        velocity.y = -velocity.y * friction;     // 反弹（能量损失）
        velocity.x *= friction;                  // 水平方向也损失能量
        isJump = false;
    }
}

// 绘制小球
void Ball::Draw()
{
    DrawCircleV(position, radius, color);
}

void Ball::Jump()
{
    if (isJump)
        return;

    velocity.y = -850;
    isJump = true;
}

void Ball::GetInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        Jump();
    }
}

bool Ball::CheckCollision(const Rectangle &rect) const
{
    // 计算小球与矩形最近的边缘点
    float closestX = std::max(rect.x, std::min(position.x, rect.x + rect.width));
    float closestY = std::max(rect.y, std::min(position.y, rect.y + rect.height));

    // 计算距离
    float distanceX = position.x - closestX;
    float distanceY = position.y - closestY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    // 判断是否碰撞
    return distanceSquared <= (radius * radius);
}

int Ball::GetLeftX()
{
    return position.x - radius;
}
