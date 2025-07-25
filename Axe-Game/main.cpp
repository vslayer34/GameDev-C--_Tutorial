#include "raylib.h"


int main()
{
    // Window Configs
    int width { 800 };
    int height { 600 };
    InitWindow(width, height, "Test");
    SetTargetFPS(60);

    // Circle Coordiants
    int centerX { width / 4 };
    int centerY { height / 3 };
    float radius { 25.0f };

    // Rectancle Coordiants
    int rectXPos { width / 2};
    int rectYPos { 0 };
    int rectMoveDirection { 5 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Start Game Logic
        DrawCircle(centerX, centerY, radius, BLUE);
        DrawRectangle(rectXPos, rectYPos, 50, 50, RED);

        // move the axe downwards
        rectYPos += rectMoveDirection;
        if (rectYPos > height - 50 || rectYPos < 0)
        {
            rectMoveDirection = -rectMoveDirection;
        }

        if (IsKeyDown(KEY_D) && centerX < width - radius)
        {
            centerX += 5;
        }
        if (IsKeyDown(KEY_A) && centerX > 0 + radius)
        {
            centerX -= 5;
        }

        // Start Game Logic
        EndDrawing();
    }
    

    return 0;
}