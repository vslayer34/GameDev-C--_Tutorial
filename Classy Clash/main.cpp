#include "raylib.h"


int main()
{
    // Window configs
    const int WIDTH { 384 };
    const int HEIGHT { 384 };
    InitWindow(WIDTH, HEIGHT, "Tahany");
    
    // File Paths
    const char *TAHANY_MAP { "Assets/nature_tileset/TahanyWorldMap.png" };

    // Load Textures
    Texture2D tahanyMap { LoadTexture(TAHANY_MAP) };

    

    Vector2 mapPos { };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw Map
        DrawTextureEx(tahanyMap, mapPos, 0.0f, 4.0f, WHITE);
        

        EndDrawing();
    }

    CloseWindow();
    

    // Unload Textures
    UnloadTexture(tahanyMap);


    return 0;
}