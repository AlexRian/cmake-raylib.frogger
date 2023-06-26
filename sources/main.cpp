#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };

    Block box{ 
        Settings::screenWidth / 2, 90, 90,
        physics.getBody("Block", Settings::screenWidth / 2, 200.0f, 90, 200, 120, true, Box, {.5f, 0.3f, 0})
    };

    Ground ground{ 
        Settings::screenWidth / 2, Settings::screenHeight, 180,
        physics.getBody("Ground", Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, Box, {0.1f, 0.1f, 0.1f})
    };

    while (!WindowShouldClose())
    {
        physics.makeWorldStep();

        box.applyPhysicsPosition();
        ground.applyPhysicsPosition();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            box.draw();
            ground.draw();
            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}