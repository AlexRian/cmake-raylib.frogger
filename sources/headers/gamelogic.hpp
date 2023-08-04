#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include "raylib.h"
#include "./engine/headers/assetsManager.hpp"
#include "./engine/headers/sound.hpp"
#include "./entities.hpp"

enum GameState
{
	Started,
	GameOver,
	Finished
};

class Gamelogic {
public:
	Gamelogic(AssetsManager* assetsManager);
	
	void drawObstacleLines();
	void drawRaftLines();
	void drawSafeZones();
	
	void checkCollisionsWithObstacles(Player* player, SoundManager* soundManager);
	void checkCollisionsWithSafeZones(Player* player, SoundManager* soundManager);
	void checkCollisionsWithRafts(Player* player, SoundManager* soundManager);
	void checkTimer(Player* player, SoundManager* soundManager);
	void makeActive(Player* player, bool timeEnded);
	void timerProcess();
	void decreaseLives();
	void addScore();
	void setPositionBuffer(int value);
	int getPositionBuffer();
	int getLives();
	int getScore();
	int getTime();
	GameState getGameState();
	bool isGameActive();
private:
	std::vector<ObstacleLine*> m_obstacleLines;
	std::vector<Obstacle*> m_obstacles;
	std::vector<RaftLine*> m_raftLines;
	std::vector<SafeZone*> m_safeZones;
	int m_lives = 5;
	int m_score = 0;
	int m_time = 200;
	int m_playerPositionYBuffer;
	bool m_gameActive = true;
	bool m_gameOver = false;
	GameState m_gameState = GameState::Started;
	std::thread* m_timerThread;
	std::thread* m_activeThread;

	void generateObstacleLines(AssetsManager* assetsManager);
	void generateRaftLines(AssetsManager* assetsManager);
	void generateSafeZones(AssetsManager* assetsManager);
};