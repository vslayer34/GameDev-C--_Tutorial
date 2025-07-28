#include "raylib.h"

int main()
{
    // Window setup
    const int WINDOW_WIDTH { 800 };
    const int WINDOW_HEIGHT { 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    // Scarfy
    const char *scargySpriteSheetPath = "Assets/textures/scarfy.png";
    Texture2D scarfySpriteSheet { LoadTexture(scargySpriteSheetPath) };
    Rectangle scarfyAnimationOffset { };
    Vector2 scarfyAnimationOffsetPos { };

    // Test rectangle
    const int RECT_WIDTH { 20 };
    const int RECT_HEIGHT { 20 };
    int rectPosY { WINDOW_HEIGHT - RECT_HEIGHT };
    int rectPosX { WINDOW_WIDTH / 2 };

    const int GRAVITY { 1 };            // gravity (1 pixel / framer^2)

    const int JUMP_FORCE { -22 };
    int jumpVelocity { 0 };

    bool grounded;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        DrawRectangle(rectPosX, rectPosY, RECT_WIDTH, RECT_HEIGHT, RED);

        // apply ground check and gravity
        grounded = (rectPosY >= WINDOW_HEIGHT - RECT_HEIGHT);
        
        if (!grounded)
        {
            jumpVelocity += GRAVITY;
        }
        else
        {
            jumpVelocity = 0;
        }

        if (IsKeyPressed(KEY_SPACE) && grounded)
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