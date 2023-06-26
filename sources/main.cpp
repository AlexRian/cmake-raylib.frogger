#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Frogger");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}