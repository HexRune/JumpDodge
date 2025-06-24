#include <raylib.h>

int main(void)
{
    // 初始化窗口
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Game Template");

    // 设置目标FPS
    SetTargetFPS(60);

    // 游戏变量
    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 20.0f;

    // 主游戏循环
    while (!WindowShouldClose())    // 检测窗口关闭按钮或ESC键
    {
        // 更新
        //----------------------------------------------------------------------------------
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // 检查墙壁碰撞（反弹小球）
        if ((ballPosition.x >= (screenWidth - ballRadius)) || (ballPosition.x <= ballRadius)) 
            ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (screenHeight - ballRadius)) || (ballPosition.y <= ballRadius)) 
            ballSpeed.y *= -1.0f;

        // 绘制
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(ballPosition, ballRadius, MAROON);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            DrawText("Press ESC to close window", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // 关闭窗口和OpenGL上下文
    CloseWindow();

    return 0;
}