#pragma once
#include<raylib.h>

class Ball
{
private:
    Vector2 position;
    Vector2 velocity;
    Color color;
    float radius;
    float gravity;
    float friction;
    bool isJump = true;
    
public:
    Ball():velocity{0,0},gravity(1500.0f),friction(0.3f){};
    ~Ball() = default;

    void Init(Vector2 position, float radius, Color color);
    void Update(float deltaTime);
    void GetInput();
    void Draw();
    void Jump();

    Vector2 GetPosition();
    float GetRadius();
    int GetLeftX();
};
