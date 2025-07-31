#include "raylib.h"

struct AnimData
{
    Rectangle spriteRect { };
    Vector2 pos { };
    int frame { };
    float animUpdateTime { };
    float animRunTime { };

    int getSpriteWidth() { return static_cast<int>(this->spriteRect.width); }
    int getSpriteHeight() { return static_cast<int>(this->spriteRect.height) ; }
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
        .animUpdateTime { 1.0f / 12.0f },
        .animRunTime { }
    };

    const int GRAVITY { 1000 };            // gravity (1 pixel / sec^2)

    const int JUMP_FORCE { -600 };          // pixel / sec
    int jumpVelocity { 0 };

    bool grounded { };

    const int NEBULAE_COUNT { 3 };
    AnimData nebulae[NEBULAE_COUNT] { };

    for (int i { 0 }; i < NEBULAE_COUNT; i++)
    {
        const int NEBULAE_INTERVAL { 450 };
        nebulae[i].spriteRect = 
        {
            .x { 0 },
            .y { 0 },
            .width { static_cast<float>(nebulaSpriteSheet.width) / 8 },
            .height { static_cast<float>(nebulaSpriteSheet.height) / 8 }
        };

        // .pos { WINDOW_DIMENSIONS[0] + 450, WINDOW_DIMENSIONS[1] - nebulaAnimData.spriteRect.height },
        nebulae[i].pos = 
        { 
            static_cast<float>(WINDOW_DIMENSIONS[0]) + (i * NEBULAE_INTERVAL), 
            static_cast<float>(WINDOW_DIMENSIONS[1] - static_cast<float>(nebulaSpriteSheet.height) / 8)
        };
        
        nebulae[i].frame = 0,
        nebulae[i].animUpdateTime = 1.0f / 16.0f;
        nebulae[i].animRunTime = 0;
    }



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        float deltaTime = GetFrameTime();

        scarfyData.animRunTime += deltaTime;
        nebulae[0].animRunTime += deltaTime;
        nebulae[1].animRunTime += deltaTime;
        nebulae[2].animRunTime += deltaTime;

        if (nebulae[1].animRunTime >= nebulae[1].animUpdateTime)
        {
            nebulae[1].animRunTime = 0.0f;
            nebulae[1].spriteRect.x = nebulae[1].frame * nebulae[1].getSpriteWidth();

            nebulae[1].frame = nebulae[1].frame >= 7 ? 0 : nebulae[1].frame + 1;
        }

        if (nebulae[2].animRunTime >= nebulae[2].animUpdateTime)
        {
            nebulae[2].animRunTime = 0.0f;
            nebulae[2].spriteRect.x = nebulae[2].frame * nebulae[2].getSpriteWidth();

            nebulae[2].frame = nebulae[2].frame >= 7 ? 0 : nebulae[2].frame + 1;
        }

        if (nebulae[0].animRunTime >= nebulae[0].animUpdateTime)
        {
            nebulae[0].animRunTime = 0.0f;
            nebulae[0].spriteRect.x = nebulae[0].frame * nebulae[0].getSpriteWidth();

            nebulae[0].frame = nebulae[0].frame >= 7 ? 0 : nebulae[0].frame + 1;
        }

        if (scarfyData.animRunTime >= scarfyData.animUpdateTime)
        {
            scarfyData.animRunTime = 0.0f;
            scarfyData.spriteRect.x = scarfyData.frame * scarfyData.getSpriteWidth();

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
        grounded = (scarfyData.pos.y >= WINDOW_DIMENSIONS[1] - scarfyData.spriteRect.height);
        
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
        nebulae[0].pos.x += nebulaVelocity * deltaTime;
        nebulae[1].pos.x += nebulaVelocity * deltaTime;
        nebulae[2].pos.x += nebulaVelocity * deltaTime;


        DrawTextureRec(scarfySpriteSheet, scarfyData.spriteRect, scarfyData.pos, WHITE);
        DrawTextureRec(nebulaSpriteSheet, nebulae[0].spriteRect, nebulae[0].pos, WHITE);

        // nebula 2
        DrawTextureRec(nebulaSpriteSheet, nebulae[1].spriteRect, nebulae[1].pos, RED);
        DrawTextureRec(nebulaSpriteSheet, nebulae[2].spriteRect, nebulae[2].pos, BLUE);
        
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    UnloadTexture(nebulaSpriteSheet);
    CloseWindow();

    return 0;
}