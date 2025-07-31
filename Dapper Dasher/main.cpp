#include "raylib.h"

struct AnimData
{
    Rectangle spriteRect { };
    Vector2 pos { };
    int frame { };
    const float ANIME_UPDATE_TIME { };
    float animRunTime { };

    int spriteWidth { static_cast<int>(spriteRect.width) };
    int spriteHeight { static_cast<int>(spriteRect.height) };
};


int main()
{
    // files paths
    const char *scargySpriteSheetPath { "Assets/textures/scarfy.png" };
    const char *nebulaSpriteSheetPath { "Assets/textures/12_nebula_spritesheet.png" };
    // Window setup
    const int WINDOW_DIMENSIONS[2] { 800, 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_DIMENSIONS[0], WINDOW_DIMENSIONS[1], "Dapper Dasher");

    // Nebula
    Texture2D nebulaSpriteSheet { LoadTexture(nebulaSpriteSheetPath) };

    AnimData nebulaAnimData
    {
        .spriteRect
        {
            .x = 0,
            .y = 0,
            .width = static_cast<float>(nebulaSpriteSheet.width / 8),
            .height = static_cast<float>(nebulaSpriteSheet.height / 8),
        },

        .pos { WINDOW_DIMENSIONS[0], WINDOW_DIMENSIONS[1] - nebulaAnimData.spriteRect.height },
        .frame { },
        .ANIME_UPDATE_TIME { 1.0f / 12.0f },
        .animRunTime { }
    };

    // Nebula 2
    AnimData nebulaAnimData2
    {
        .spriteRect
        {
            .x = 0,
            .y = 0,
            .width = static_cast<float>(nebulaSpriteSheet.width / 8),
            .height = static_cast<float>(nebulaSpriteSheet.height / 8),
        },

        .pos { WINDOW_DIMENSIONS[0] + 450, WINDOW_DIMENSIONS[1] - nebulaAnimData.spriteRect.height },
        .frame { },
        .ANIME_UPDATE_TIME { 1.0f / 16.0f },
        .animRunTime { }
    };

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
            .x = WINDOW_DIMENSIONS[0] / 2 - scarfyData.spriteRect.width,
            .y = WINDOW_DIMENSIONS[1] - scarfyData.spriteRect.height
        },

        .frame { },
        .ANIME_UPDATE_TIME { 1.0f / 12.0f },
        .animRunTime { }
    };

    const int GRAVITY { 1000 };            // gravity (1 pixel / sec^2)

    const int JUMP_FORCE { -600 };          // pixel / sec
    int jumpVelocity { 0 };

    bool grounded;




    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        float deltaTime = GetFrameTime();

        scarfyData.animRunTime += deltaTime;
        nebulaAnimData.animRunTime += deltaTime;
        nebulaAnimData2.animRunTime += deltaTime;

        if (nebulaAnimData2.animRunTime >= nebulaAnimData2.ANIME_UPDATE_TIME)
        {
            nebulaAnimData2.animRunTime = 0.0f;
            nebulaAnimData2.spriteRect.x = nebulaAnimData2.frame * nebulaAnimData2.spriteWidth;

            nebulaAnimData2.frame = nebulaAnimData2.frame >= 7 ? 0 : nebulaAnimData2.frame + 1;
        }

        if (nebulaAnimData.animRunTime >= nebulaAnimData.ANIME_UPDATE_TIME)
        {
            nebulaAnimData.animRunTime = 0.0f;
            nebulaAnimData.spriteRect.x = nebulaAnimData.frame * nebulaAnimData.spriteWidth;

            nebulaAnimData.frame = nebulaAnimData.frame >= 7 ? 0 : nebulaAnimData.frame + 1;
        }

        if (scarfyData.animRunTime >= scarfyData.ANIME_UPDATE_TIME)
        {
            scarfyData.animRunTime = 0.0f;
            scarfyData.spriteRect.x = scarfyData.frame * scarfyData.spriteWidth;

            if (!grounded)
            {
                scarfyData.frame = 0;
            }
            else
            {
                scarfyData.frame = scarfyData.frame >= 5 ? 0 : scarfyData.frame + 1;
            }
        }

        // apply ground check and gravity
        grounded = (scarfyData.pos.y >= WINDOW_DIMENSIONS[1] - scarfyData.spriteHeight);
        
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

        scarfyData.pos.y += jumpVelocity * deltaTime;
        nebulaAnimData.pos.x += nebulaVelocity * deltaTime;
        nebulaAnimData2.pos.x += nebulaVelocity * deltaTime;


        DrawTextureRec(scarfySpriteSheet, scarfyData.spriteRect, scarfyData.pos, WHITE);
        DrawTextureRec(nebulaSpriteSheet, nebulaAnimData.spriteRect, nebulaAnimData.pos, WHITE);

        // nebula 2
        DrawTextureRec(nebulaSpriteSheet, nebulaAnimData2.spriteRect, nebulaAnimData2.pos, RED);
        
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    UnloadTexture(nebulaSpriteSheet);
    CloseWindow();

    return 0;
}