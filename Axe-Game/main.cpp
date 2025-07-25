#include "raylib.h"


int main()
{
    // Window Configs
    int width { 800 };
    int height { 600 };
    InitWindow(width, height, "Test");
    SetTargetFPS(60);

    // Circle Coordiants
    int centerX { width / 4 };
    int centerY { height / 3 };
    float radius { 25.0f };
    // Circle collision edges
    int circleLeftEdge { centerX - (int)radius };
    int circleRightEdge { centerX + (int)radius };
    int circleUpperEdge { centerY - (int)radius };
    int circleLowerEdge { centerY + (int)radius };

    // Rectancle Coordiants
    int rectXPos { width / 2};
    int rectYPos { 0 };
    int rectLength { 50 };
    int rectMoveDirection { 5 };
    // Rectancle collision edges
    int rectLeftEdge { rectXPos };
    int rectRightEdge { rectXPos + rectLength };
    int rectUpperEdge { rectYPos };
    int rectLowerEdge { rectYPos + rectLength };

    // Game Over Text
    int labelFont { 20 };
    int labelXPos { width / 2 };
    int labelYPos { (height / 2) - (labelFont / 2) };
    bool collisionWithAxe { false };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // Start Game Logic

        

        if (collisionWithAxe)
        {
            DrawText("Game Over", labelXPos, labelYPos, labelFont, RED);
        }
        else
        {
            DrawCircle(centerX, centerY, radius, BLUE);
            DrawRectangle(rectXPos, rectYPos, rectLength, rectLength, RED);

            // Update collision edges
            circleLeftEdge = centerX - radius;
            circleRightEdge = centerX + radius;
            circleUpperEdge = centerY - radius;
            circleLowerEdge = centerY + radius;

            rectLeftEdge = rectXPos;
            rectRightEdge = rectXPos + rectLength;
            rectUpperEdge = rectYPos;
            rectLowerEdge = rectYPos + rectLength;

            if (rectLowerEdge > circleUpperEdge &&
                rectUpperEdge < circleLowerEdge &&
                rectLeftEdge < circleRightEdge &&
                rectRightEdge > circleLeftEdge)
            {
                collisionWithAxe = true;
            }

            // move the axe downwards
            rectYPos += rectMoveDirection;
            if (rectYPos > height - rectLength || rectYPos < 0)
            {
                rectMoveDirection = -rectMoveDirection;
            }

            if (IsKeyDown(KEY_D) && centerX < width - radius)
            {
                centerX += 5;
            }
            if (IsKeyDown(KEY_A) && centerX > 0 + radius)
            {
                centerX -= 5;
            }
        }
        

        // Start Game Logic
        EndDrawing();
    }
    

    return 0;
}