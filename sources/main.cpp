#include <stdio.h>
#include "raylib.h"
#include "./engine/debug.hpp"
#include "./engine/physics.hpp"
#include "./engine/assetsManager.hpp"
#include "./entities.hpp"
#include "./gamelogic.hpp"
#include "./ui.hpp"

std::vector<TextureData> textureData{
    {"player", ASSETS_PATH"entities/player.png"},
    {"car", ASSETS_PATH"entities/car.png"},
    {"log", ASSETS_PATH"entities/log.png"}
};

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Frogger");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    AssetsManager assetsManager{ textureData };

    Player player { Settings::screenWidth / 2, Settings::screenHeight - 25, 0, 1, assetsManager.getTexture("player")};

    Ground ground{ Settings::screenWidth / 2, Settings::screenHeight - 175, 180, Settings::screenWidth, 250 };
    Water water{ Settings::screenWidth / 2, 225, 180, Settings::screenWidth, 250 };
    Grass topGrass{ Settings::screenWidth / 2, 375, 180, Settings::screenWidth, 50 };
    Grass bottomGrass{ Settings::screenWidth / 2, Settings::screenHeight - 25, 180, Settings::screenWidth, 50 };
    Grass safeZone{ Settings::screenWidth / 2, 75, 180, Settings::screenWidth, 50 };

    Gamelogic gamelogic{ &assetsManager };
    UI ui{ &assetsManager };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W)) player.moveUp();
        if (IsKeyPressed(KEY_S)) player.moveDown();
        if (IsKeyPressed(KEY_A)) player.moveLeft(Settings::playerStepWidth);
        if (IsKeyPressed(KEY_D)) player.moveRight(Settings::playerStepWidth);

        gamelogic.checkCollisionsWithObstacles(&player);
        gamelogic.checkCollisionsWithRafts(&player);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            water.draw();
            ground.draw();
            
            bottomGrass.draw();
            topGrass.draw();
            safeZone.draw();

            gamelogic.drawObstacleLines();
            gamelogic.drawRaftLines();
            
            player.draw();

            ui.draw(gamelogic.getScore(), gamelogic.getLives(), gamelogic.getTime());
            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}