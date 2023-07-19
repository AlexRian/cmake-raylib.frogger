#pragma once
#include <vector>
#include "raylib.h"
#include "./engine/assetsManager.hpp"
#include "./entities.hpp"

class Gamelogic {
public:
	Gamelogic(AssetsManager* assetsManager) {
		generateObstacleLines(assetsManager);
	}
	void generateObstacleLines(AssetsManager* assetsManager) {
		for (size_t i = 1; i < 6; i++)
		{
			m_obstacleLines.push_back(
				new ObstacleLine{ 
					Settings::screenHeight - (50 * (int)i) - 25,
					GetRandomValue(0, 1) == 0 ? 1 : -1,
					assetsManager->getTexture("car") 
				}
			);
		}
	}
	
	void drawObstacleLines() {
		for each (ObstacleLine* obstacleLine in m_obstacleLines)
		{
			obstacleLine->draw();
		}
	}

private:
	std::vector<ObstacleLine*> m_obstacleLines;
};