#include <stdio.h>
#include "raylib.h"
#include "./engine/headers/debug.hpp"
#include "./engine/headers/physics.hpp"
#include "./engine/headers/assetsManager.hpp"
#include "./engine/headers/sound.hpp"
#include "./headers/entities.hpp"
#include "./headers/gamelogic.hpp"
#include "./headers/ui.hpp"

std::vector<TextureData> textureData{
    { "player", ASSETS_PATH"entities/player.png" },
    { "car", ASSETS_PATH"entities/car.png" },
    { "log", ASSETS_PATH"entities/log.png" },
    { "death", ASSETS_PATH"death.png" }
};

std::vector<SoundData> soundData{
    { "death", ASSETS_PATH"sounds/beep.wav" },
    { "win", ASSETS_PATH"sounds/win.wav" },
};

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Frogger");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    AssetsManager assetsManager{ textureData };
    SoundManager soundManager{ soundData };

    Player player { Settings::screenWidth / 2, Settings::screenHeight - 25, 0, 1, assetsManager.getTexture("player"), assetsManager.getTexture("death") };

    Ground ground{ Settings::screenWidth / 2, Settings::screenHeight - 175, 180, Settings::screenWidth, 250 };
    Water water{ Settings::screenWidth / 2, 225, 180, Settings::screenWidth, 250 };
    Grass topGrass{ Settings::screenWidth / 2, 375, 180, Settings::screenWidth, 50 };
    Grass bottomGrass{ Settings::screenWidth / 2, Settings::screenHeight - 25, 180, Settings::screenWidth, 50 };
    Grass shore{ Settings::screenWidth / 2, 75, 180, Settings::screenWidth, 50 };

    Gamelogic gamelogic{ &assetsManager };
    UI ui{ &assetsManager };

    gamelogic.setPositionBuffer(player.getPosition().y);
    while (!WindowShouldClose())
    {
        gamelogic.checkCollisionsWithObstacles(&player, &soundManager);
        gamelogic.checkCollisionsWithRafts(&player, &soundManager);
        gamelogic.checkCollisionsWithSafeZones(&player, &soundManager);
        gamelogic.checkTimer(&player, &soundManager);

        if (gamelogic.isGameActive()) {
            if (IsKeyPressed(KEY_W)) {
                player.moveUp();
                if (gamelogic.getPositionBuffer() > player.getPosition().y) {
                    gamelogic.setPositionBuffer(player.getPosition().y);
                    gamelogic.addScore();
                }
            };
            if (IsKeyPressed(KEY_S)) player.moveDown();
            if (IsKeyPressed(KEY_A)) player.moveLeft(Settings::playerStepWidth);
            if (IsKeyPressed(KEY_D)) player.moveRight(Settings::playerStepWidth);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            water.draw();
            ground.draw();
            
            bottomGrass.draw();
            topGrass.draw();
            shore.draw();

            gamelogic.drawObstacleLines();
            gamelogic.drawRaftLines();
            gamelogic.drawSafeZones();
            
            player.draw();

            ui.draw(gamelogic.getScore(), gamelogic.getLives(), gamelogic.getTime(), gamelogic.getGameState());
            debug.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}