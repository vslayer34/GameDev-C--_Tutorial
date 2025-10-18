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


bool isGrounded(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.spriteRect.height;
}

AnimData updateAnimDataAnimations(AnimData data, float deltaTime, int maxFrameCount)
{
    data.animRunTime += deltaTime;

    if (data.animRunTime >= data.animUpdateTime)
    {
        data.animRunTime = 0.0f;
        data.spriteRect.x = data.frame * data.getSpriteWidth();

        data.frame = data.frame >= maxFrameCount ? 0 : data.frame + 1;
    }
    
    return data;
}


int main()
{
    // files paths
    const char *scargySpriteSheetPath { "Assets/textures/scarfy.png" };
    const char *nebulaSpriteSheetPath { "Assets/textures/12_nebula_spritesheet.png" };
    const char *backgroundSprite { "Assets/textures/far-buildings.png" };

    // Window setup
    const int WINDOW_DIMENSIONS[2] { 800, 600 };
    SetTargetFPS(60);

    InitWindow(WINDOW_DIMENSIONS[0], WINDOW_DIMENSIONS[1], "Dapper Dasher");

    // background
    Texture2D backgroundTexture { LoadTexture(backgroundSprite) };

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

    const int NEBULAE_COUNT { 6 };
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

    float bgXSpeed { };





    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Begin Game Logic

        float deltaTime = GetFrameTime();
        
        // scrolling and updating the background
        Vector2 backgroundPos { bgXSpeed, 0.0f };
        bgXSpeed -= 20 * deltaTime;
        DrawTextureEx(backgroundTexture, backgroundPos, 0.0f, 3.3f, WHITE);

        scarfyData.animRunTime += deltaTime;

        for (int i { 0 }; i < NEBULAE_COUNT; i++)
        {

            // Update Nebulae animations

            nebulae[i] = updateAnimDataAnimations(nebulae[i], deltaTime, 7);

            // Update Nebula position
            nebulae[i].pos.x += nebulaVelocity * deltaTime;

            // Draw Nebulae
            DrawTextureRec(nebulaSpriteSheet, nebulae[i].spriteRect, nebulae[i].pos, WHITE);
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
        grounded = isGrounded(scarfyData, WINDOW_DIMENSIONS[1]);
        
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


        DrawTextureRec(scarfySpriteSheet, scarfyData.spriteRect, scarfyData.pos, WHITE);
        
        // End Game Logic
        EndDrawing();
    }

    UnloadTexture(scarfySpriteSheet);
    UnloadTexture(nebulaSpriteSheet);
    UnloadTexture(backgroundTexture);
    CloseWindow();

    return 0;
}