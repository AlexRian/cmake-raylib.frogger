#pragma once
#include <vector>
#include "raylib.h"
#include "./engine/assetsManager.hpp"
#include "./entities.hpp"

class Gamelogic {
public:
	Gamelogic(AssetsManager* assetsManager) {
		generateObstacleLines(assetsManager);
		generateRaftLines(assetsManager);
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
	void generateRaftLines(AssetsManager* assetsManager) {
		for (size_t i = 1; i < 6; i++)
		{
			m_raftLines.push_back(
				new RaftLine{
					(50 * (int)i) + 75,
					GetRandomValue(0, 1) == 0 ? 1 : -1,
					assetsManager->getTexture("log")
				}
			);
		}
	}
	void drawObstacleLines() {
		for each (ObstacleLine* obstacleLine in m_obstacleLines)
		{
			if (m_gameActive) {
				obstacleLine->makeMove();
			}
			obstacleLine->draw();
		}
	}
	void drawRaftLines() {
		for each (RaftLine* raftLine in m_raftLines)
		{
			if (m_gameActive) {
				raftLine->makeMove();
			}
			raftLine->draw();
		}
	}
	void checkCollisionsWithObstacles(Player player) {
		for each (ObstacleLine* obstacleLine in m_obstacleLines)
		{
			for each (Obstacle obstacle in obstacleLine->getObstacles())
			{
				bool collision = CheckCollisionRecs(player.getBody(), obstacle.getBody());
				if (collision) {
					m_gameActive = false;
				}
			}
		}
	}
	void checkCollisionsWithRafts(Player& player) {
		for each (RaftLine* raftLine in m_raftLines)
		{
			for each (Raft raft in raftLine->getRafts())
			{
				bool collision = CheckCollisionRecs(player.getBody(), raft.getBody());
				if (collision) {
					raftLine->getDirection() == 1 ? player.moveRight(1) : player.moveLeft(1);
				}
			}
		}
	}
	int getLives() {
		return m_lives;
	}
	int getScore() {
		return m_score;
	}
	int getTime() {
		return m_time;
	}
private:
	std::vector<ObstacleLine*> m_obstacleLines;
	std::vector<RaftLine*> m_raftLines;
	int m_lives = 5;
	int m_score = 100;
	int m_time = 100;
	bool m_gameActive = true;
};