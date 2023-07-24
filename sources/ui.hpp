#pragma once
#include "raylib.h"
#include <stdio.h>
#include <string>

class UI {
public:
	UI(AssetsManager* assetsManager) {
		m_healtTexture = assetsManager->getTexture("player");
	}
	void draw(int score, int lives, int time) {
		DrawText(TextFormat("Score: %06i", score), (Settings::screenWidth / 2) - 100, 10, 20, DARKGRAY);

		DrawText("Time:", 10, 10, 20, DARKGRAY);
		DrawRectangle(60, 10, 200, 20, GREEN);

		DrawText("Lives:", Settings::screenWidth - 230, 10, 20, DARKGRAY);

		for (size_t i = 1; i < lives + 1; i++)
		{
			Rectangle sourceRec = { 0.0f, 0.0f, (float)m_healtTexture->width, (float)m_healtTexture->height };
			Rectangle body = { Settings::screenWidth - (i * 30), 20, (float)m_healtTexture->width / 2, (float)m_healtTexture->height / 2};
			DrawTexturePro(
				*m_healtTexture,
				sourceRec,
				body,
				{ (float)m_healtTexture->width / 4, (float)m_healtTexture->height / 4 },
				(float)0,
				WHITE
			);
		}
	}
private:
	Texture2D* m_healtTexture;
};