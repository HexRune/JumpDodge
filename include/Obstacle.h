#pragma once
#include "raylib.h"

class Obstacle {
private:
    Rectangle rect;     // 障碍物的矩形区域
    Color color;        // 障碍物颜色
    float speed;        // 向左移动的速度
    bool scored;

public:
    Obstacle() = default;
    ~Obstacle() = default;

    void Init(Rectangle rect, Color color, float speed);
    void Update(float deltaTime);  // 更新障碍物位置
    void Draw();                   // 绘制障碍物
    Rectangle GetRect() const;     // 获取障碍物的矩形（用于碰撞检测）
    bool IsOutOfScreen() const;    // 检查障碍物是否完全离开屏幕
    int GetRightX() const;
    bool IsScored();
    void MarkAsScored();
    void Reset();
    
};