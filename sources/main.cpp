#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"
#include "./engine/assetsManager.hpp"

std::vector<TextureData> textureData{
    {"player", ASSETS_PATH"entities/player.png"}
};

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Frogger");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    AssetsManager assetsManager{ textureData };

    Player player { 100, 100, 0, 64, 64, assetsManager.getTexture("player")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            player.draw();

            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}