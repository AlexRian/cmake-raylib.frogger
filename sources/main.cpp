#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./entities.hpp"
#include "./engine/assetsManager.hpp"

std::vector<TextureData> textureData{
    {"player", ASSETS_PATH"entities/player.png"},
    {"car", ASSETS_PATH"entities/car.png"}
};

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Frogger");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    AssetsManager assetsManager{ textureData };

    Player player { Settings::screenWidth / 2, Settings::screenHeight - 100, 0, 1, assetsManager.getTexture("player")};

    ObstacleLine obstacleLine{ 100, -1, assetsManager.getTexture("player") };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W)) player.moveUp();
        if (IsKeyPressed(KEY_A)) player.moveLeft();
        if (IsKeyPressed(KEY_S)) player.moveDown();
        if (IsKeyPressed(KEY_D)) player.moveRight();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            obstacleLine.draw();

            player.draw();

            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}