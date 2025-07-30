#include "raylib.h"

struct AnimData
{
    Rectangle spriteRect { };
    Vector2 pos { };
    int frame { };
    const float ANIME_UPDATE_TIME { };
    float animRunTime { };
};


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
    Rectangle nebulaSpriteRect
    {
        .x = 0,
        .y = 0,
        .width = nebulaSpriteSheet.width / 8,
        .height = nebulaSpriteSheet.height / 8,
    };
    Vector2 nebulaPos { WINDOW_WIDTH, WINDOW_HEIGHT - nebulaSpriteRect.height };

    // Nebula 2
    Texture2D nebulaSpriteSheet2 { LoadTexture(nebulaSpriteSheetPath) };
    Rectangle nebulaSpriteRect2
    {
        .x = 0,
        .y = 0,
        .width = nebulaSpriteSheet.width / 8,
        .height = nebulaSpriteSheet.height / 8,
    };
    Vector2 nebulaPos2 { WINDOW_WIDTH + 450, WINDOW_HEIGHT - nebulaSpriteRect.height };

    int nebulaVelocity { -600 };                // pixel/sec


    // Scarfy
    Texture2D scarfySpriteSheet { LoadTexture(scargySpriteSheetPath) };

    AnimData scarfyData
    {
        .spriteRect
        {
            .x { 0 },
            .y { 0 },
            .width { static_cast<float>(scarfySpriteSheet.width) / 6 },
            .height { static_cast<float>(scarfySpriteSheet.height) }
        },

        .pos
        {
            .x = WINDOW_WIDTH / 2 - scarfyData.spriteRect.width,
            .y = WINDOW_HEIGHT - scarfyData.spriteRect.height
        },

        .frame { },
        .ANIME_UPDATE_TIME { 1.0f / 12.0f },
        .animRunTime { }
    };
    
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
    // scarfy
    int scarfyFrame { };
    const float SCARFY_FRAME_UPDATE_TIME { 1.0f / 12.0f };
    float scarfyAnimationRunTime { };

    // nebula
    int nebulaFrame { };
    const float NEBULA_FRAME_UPDATE_TIME { 1.0f / 12.0f };
    float nebulaAnimationRunTime { };

    // nebula 2
    int nebulaFrame2 { };
    const float NEBULA_FRAME_UPDATE_TIME_2 { 1.0f / 16.0f };
    float nebulaAnimationRunTime2 { };




    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        float deltaTime = GetFrameTime();

        scarfyAnimationRunTime += deltaTime;
        nebulaAnimationRunTime += deltaTime;
        nebulaAnimationRunTime2 += deltaTime;

        if (nebulaAnimationRunTime2 >= NEBULA_FRAME_UPDATE_TIME_2)
        {
            nebulaAnimationRunTime2 = 0.0f;
            nebulaSpriteRect2.x = nebulaFrame2 * nebulaSpriteRect2.width;

            nebulaFrame2 = nebulaFrame2 >= 7 ? 0 : nebulaFrame2 + 1;
        }

        if (nebulaAnimationRunTime >= NEBULA_FRAME_UPDATE_TIME)
        {
            nebulaAnimationRunTime = 0.0f;
            nebulaSpriteRect.x = nebulaFrame * nebulaSpriteRect.width;

            nebulaFrame = nebulaFrame >= 7 ? 0 : nebulaFrame + 1;
        }

        if (scarfyAnimationRunTime >= SCARFY_FRAME_UPDATE_TIME)
        {
            scarfyAnimationRunTime = 0.0f;
            scarfySpriteRect.x = scarfyFrame * scarfySpriteRect.width;

            if (!grounded)
            {
                scarfyFrame = 0;
            }
            else
            {
                scarfyFrame = scarfyFrame >= 5 ? 0 : scarfyFrame + 1;
            }
        }

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
        nebulaPos.x += nebulaVelocity * deltaTime;
        nebulaPos2.x += nebulaVelocity * deltaTime;


        DrawTextureRec(scarfySpriteSheet, scarfySpriteRect, scarfyPos, WHITE);
        DrawTextureRec(nebulaSpriteSheet, nebulaSpriteRect, nebulaPos, WHITE);

        // nebula 2
        DrawTextureRec(nebulaSpriteSheet2, nebulaSpriteRect2, nebulaPos2, RED);
        
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    UnloadTexture(nebulaSpriteSheet);
    CloseWindow();

    return 0;
}