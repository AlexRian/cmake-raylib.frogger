#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include "raylib.h"
#include "./engine/assetsManager.hpp"
#include "./engine/sound.hpp"
#include "./entities.hpp"

class Gamelogic {
public:
	Gamelogic(AssetsManager* assetsManager) {
		generateObstacleLines(assetsManager);
		generateRaftLines(assetsManager);

		std::thread* thread_object = new std::thread(&Gamelogic::timerProcess, this);
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
	void checkCollisionsWithObstacles(Player* player, SoundManager* soundManager) {
		if (!m_gameActive) return;
		for (ObstacleLine* obstacleLine : m_obstacleLines)
		{
			for (Obstacle* obstacle : obstacleLine->getObstacles())
			{
				bool collision = CheckCollisionRecs(player->getBody(), obstacle->getBody());
				if (collision) {
					soundManager->playSound("death");
					--m_lives;
					m_gameActive = false;
					std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player );
				}
			}
		}
	}
	void checkCollisionsWithRafts(Player* player, SoundManager* soundManager) {
		if (!m_gameActive) return;
		bool collision = false;
		for (RaftLine* raftLine : m_raftLines)
		{
			for (Raft* raft : raftLine->getRafts())
			{
				bool possibleCollision = CheckCollisionRecs(player->getBody(), raft->getBody());
				if (possibleCollision) {
					collision = true;
					raftLine->getDirection() == 1 ? player->moveRight(1) : player->moveLeft(1);
					break;
				}
			}
		}
		if (player->getPosition().y < 350 && m_gameActive && !collision) {
			soundManager->playSound("death");
			--m_lives;
			m_gameActive = false;
			std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player);
		}
	}
	void makeActive(Player* player) {
		player->showDeathIcon();
		std::this_thread::sleep_for(std::chrono::milliseconds(900));
		player->hideDeathIcon();
		player->setPosition({ Settings::screenWidth / 2, Settings::screenHeight - 25 });
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		m_time = 200;
		m_gameActive = true;
	}
	void timerProcess() {
		while (m_time > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			m_time -= 10;
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
	bool isGameActive() {
		return m_gameActive;
	}
private:
	std::vector<ObstacleLine*> m_obstacleLines;
	std::vector<Obstacle*> m_obstacles;
	std::vector<RaftLine*> m_raftLines;
	int m_lives = 5;
	int m_score = 100;
	int m_time = 200;
	bool m_gameActive = true;
};