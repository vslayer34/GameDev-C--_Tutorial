#include "raylib.h"

int main()
{
    // Window setup
    const int WINDOW_WIDTH { 800 };
    const int WINDOW_HEIGHT { 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    // Test rectangle
    const int RECT_WIDTH { 20 };
    const int RECT_HEIGHT { 20 };
    int rectPosY { WINDOW_HEIGHT - RECT_HEIGHT };
    int rectPosX { WINDOW_WIDTH / 2 };

    const int GRAVITY { 1 };            // gravity (1 pixel / framer^2)

    const int JUMP_FORCE { -10 };
    int jumpVelocity { 0 };

    bool isGrounded;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        DrawRectangle(rectPosX, rectPosY, RECT_WIDTH, RECT_HEIGHT, RED);

        // apply ground check and gravity
        isGrounded = (rectPosY >= WINDOW_HEIGHT - RECT_HEIGHT);
        
        if (!isGrounded)
        {
            jumpVelocity += GRAVITY;
        }
        else
        {
            jumpVelocity = 0;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            // rectPosY += JUMP_VELOCITY;
            jumpVelocity += JUMP_FORCE;
        }

        rectPosY += jumpVelocity;
        
        
        // End Game Logic
        EndDrawing();
    }
    CloseWindow();

    return 0;
}