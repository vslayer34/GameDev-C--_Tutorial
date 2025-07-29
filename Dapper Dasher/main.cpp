#include "raylib.h"

int main()
{
    // files paths
    const char *scargySpriteSheetPath { "Assets/textures/scarfy.png" };
    const char *nebulaSpriteSheetPath { "Assets/textures/12_nebula_spritesheet.png" };
    // Window setup
    const int WINDOW_WIDTH { 800 };
    const int WINDOW_HEIGHT { 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

    // Nebula
    Texture2D nebulaSpriteSheet { LoadTexture(nebulaSpriteSheetPath) };

    // Scarfy
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

    const int GRAVITY { 1000 };            // gravity (1 pixel / sec^2)

    const int JUMP_FORCE { -600 };          // pixel / sec
    int jumpVelocity { 0 };

    bool grounded;

    // animations
    int frame { };
    const float framesUpdateTime { 1.0f / 12.0f };
    float animationTime { };


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        float deltaTime = GetFrameTime();

        animationTime += deltaTime;

        if (animationTime >= framesUpdateTime)
        {
            animationTime = 0;
            scarfySpriteRect.x = frame * scarfySpriteRect.width;
            frame = frame >= 5 ? 0 : frame + 1;
        }

        DrawTextureRec(scarfySpriteSheet, scarfySpriteRect, scarfyPos, WHITE);

        // apply ground check and gravity
        grounded = (scarfyPos.y >= WINDOW_HEIGHT - scarfySpriteRect.height);
        
        if (!grounded)
        {
            jumpVelocity += GRAVITY * deltaTime;
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

        scarfyPos.y += jumpVelocity * deltaTime;
        
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    UnloadTexture(nebulaSpriteSheet);
    CloseWindow();

    return 0;
}