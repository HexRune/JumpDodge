#pragma once
#include "raylib.h"

class Ball
{
private:
    Vector2 position;       // 当前位置
    Vector2 velocity;       // 当前速度
    int radius;             // 小球半径
    Color color;            // 小球颜色
    float gravity;          // 重力加速度
    float friction;         // 地面摩擦力（反弹能量损失）
    bool isJump = true;     // 是否正在跳跃

public:
    // 重力设为 500 像素/秒²，反弹摩擦系数 0.8; // 构造函数（指定初始位置和属性）
    Ball():velocity{0, 0},gravity(1500.0f), friction(0.3f) {} 
    ~Ball() = default;                               // 默认析构函数

    void Init(Vector2 position, int radius, Color color);
    void Update(float deltaTime); // 更新小球位置（deltaTime 为帧时间）
    void Draw();                  // 绘制小球
    void Jump();                  // 跳跃
    void GetInput();              // 按键侦测
    bool CheckCollision(const Rectangle& rect) const;  // 检测与矩形的碰撞
    int GetLeftX();

};