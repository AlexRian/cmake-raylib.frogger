#pragma once
#include "raylib.h"
#include <stdio.h>
#include <string>
#include "engine/headers/assetsManager.hpp"
#include "headers/settings.hpp"
#include "headers/gamelogic.hpp"

class UI {
public:
	UI(AssetsManager* assetsManager);

	void draw(int score, int lives, int time, GameState gameState);
private:
	Texture2D* m_healtTexture;
};