#include "raylib.h"


int main()
{
    int width { 800 };
    int height { 600 };
    InitWindow(width, height, "Test");

    int centerX { width / 2 };
    int centerY { height / 2 };
    float radius { 25.0f };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(centerX, centerY, radius, BLUE);
        EndDrawing();
    }
    

    return 0;
}