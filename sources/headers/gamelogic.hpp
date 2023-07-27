#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include "raylib.h"
#include "./engine/headers/assetsManager.hpp"
#include "./engine/headers/sound.hpp"
#include "./entities.hpp"

class Gamelogic {
public:
	Gamelogic(AssetsManager* assetsManager);
	
	void drawObstacleLines();
	void drawRaftLines();
	void drawSafeZones();
	
	void checkCollisionsWithObstacles(Player* player, SoundManager* soundManager);
	void checkCollisionsWithSafeZones(Player* player, SoundManager* soundManager);
	void checkCollisionsWithRafts(Player* player, SoundManager* soundManager);
	
	void makeActive(Player* player);
	void timerProcess();
	int getLives();
	int getScore();
	int getTime();
	bool isGameActive();
private:
	std::vector<ObstacleLine*> m_obstacleLines;
	std::vector<Obstacle*> m_obstacles;
	std::vector<RaftLine*> m_raftLines;
	std::vector<SafeZone*> m_safeZones;
	int m_lives = 5;
	int m_score = 0;
	int m_time = 200;
	bool m_gameActive = true;

	void generateObstacleLines(AssetsManager* assetsManager);
	void generateRaftLines(AssetsManager* assetsManager);
	void generateSafeZones(AssetsManager* assetsManager);
};