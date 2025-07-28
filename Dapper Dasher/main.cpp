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
    Rectangle scarfySpriteRect
    { 
        .x = 0,
        .y = 0,
        .width = static_cast<float>(scarfySpriteSheet.width) / 6,
        .height = static_cast<float>(scarfySpriteSheet.height)
    };
    Vector2 scarfyPos
    {
        .x = WINDOW_WIDTH / 2 - scarfySpriteRect.width,
        .y = WINDOW_HEIGHT - scarfySpriteRect.height
    };

    const int GRAVITY { 1 };            // gravity (1 pixel / framer^2)

    const int JUMP_FORCE { -22 };
    int jumpVelocity { 0 };

    bool grounded;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        DrawTextureRec(scarfySpriteSheet, scarfySpriteRect, scarfyPos, WHITE);

        // apply ground check and gravity
        grounded = (scarfyPos.y >= WINDOW_HEIGHT - scarfySpriteRect.height);
        
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

        scarfyPos.y += jumpVelocity;
        
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    CloseWindow();

    return 0;
}