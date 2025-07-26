#include "raylib.h"

int main()
{
    // Window setup
    const int WINDOW_WIDTH { 800 };
    const int WINDOW_HEIGHT { 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic
        
        
        // End Game Logic
        EndDrawing();
    }
    CloseWindow();

    return 0;
}