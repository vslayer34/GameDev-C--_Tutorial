#include "raylib.h"


int main()
{
    // Window Configs
    int width { 800 };
    int height { 600 };
    InitWindow(width, height, "Test");
    SetTargetFPS(60);

    // Circle Coordiants
    int centerX { width / 2 };
    int centerY { height / 2 };
    float radius { 25.0f };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Start Game Logic
        DrawCircle(centerX, centerY, radius, BLUE);

        if (IsKeyDown(KEY_D))
        {
            centerX = centerX + 5;
        }
        if (IsKeyDown(KEY_A))
        {
            centerX = centerX - 5;
        }

        // Start Game Logic
        EndDrawing();
    }
    

    return 0;
}