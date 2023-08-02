#include "headers/ui.hpp"
#include "headers/gamelogic.hpp"

UI::UI(AssetsManager* assetsManager) {
	m_healtTexture = assetsManager->getTexture("player");
}
void UI::draw(int score, int lives, int time, GameState gameState) {
	DrawText(TextFormat("Score: %06i", score), (Settings::screenWidth / 2) - 100, 10, 20, DARKGRAY);

	DrawText("Time:", 10, 10, 20, DARKGRAY);
	DrawRectangle(60, 10, time, 20, GREEN);

	DrawText("Lives:", Settings::screenWidth - 230, 10, 20, DARKGRAY);

	for (size_t i = 1; i < lives + 1; i++)
	{
		Rectangle sourceRec = { 0.0f, 0.0f, (float)m_healtTexture->width, (float)m_healtTexture->height };
		Rectangle body = { Settings::screenWidth - (i * 30), 20, (float)m_healtTexture->width / 2, (float)m_healtTexture->height / 2 };
		DrawTexturePro(
			*m_healtTexture,
			sourceRec,
			body,
			{ (float)m_healtTexture->width / 4, (float)m_healtTexture->height / 4 },
			(float)0,
			WHITE
		);
	}

	if (gameState == GameState::GameOver) {
		DrawRectangle(Settings::screenWidth / 2 - 150, Settings::screenHeight / 2 - 150, 300, 300, WHITE);
		DrawText("Game", Settings::screenWidth / 2 - 50, Settings::screenHeight / 2 - 40, 40, BLACK);
		DrawText("Over", Settings::screenWidth / 2 - 50, Settings::screenHeight / 2, 40, BLACK);
	}
}