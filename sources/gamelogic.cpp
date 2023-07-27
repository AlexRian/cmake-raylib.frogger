#include "headers/gamelogic.hpp"

Gamelogic::Gamelogic(AssetsManager* assetsManager) {
	generateObstacleLines(assetsManager);
	generateRaftLines(assetsManager);
	generateSafeZones(assetsManager);

	std::thread* thread_object = new std::thread(&Gamelogic::timerProcess, this);
}
void Gamelogic::drawObstacleLines() {
	for each (ObstacleLine * obstacleLine in m_obstacleLines)
	{
		if (m_gameActive) {
			obstacleLine->makeMove();
		}
		obstacleLine->draw();
	}
}
void Gamelogic::drawRaftLines() {
	for each (RaftLine * raftLine in m_raftLines)
	{
		if (m_gameActive) {
			raftLine->makeMove();
		}
		raftLine->draw();
	}
}
void Gamelogic::drawSafeZones() {
	for each (SafeZone * safezone in m_safeZones)
	{
		safezone->draw();
	}
}
void Gamelogic::checkCollisionsWithObstacles(Player* player, SoundManager* soundManager) {
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
				player->showDeathIcon();
				std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player);
			}
		}
	}
}
void Gamelogic::checkCollisionsWithSafeZones(Player* player, SoundManager* soundManager) {
	if (!m_gameActive) return;
	for (SafeZone* safezone : m_safeZones)
	{
		bool collision = CheckCollisionRecs(player->getBody(), safezone->getBody());
		if (collision) {
			m_gameActive = false;
			if (!safezone->isOccupied()) {
				soundManager->playSound("win");
				player->hidePlayer();
				safezone->makeOccupied();
				m_score += 100;
				std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player);
			}
			else {
				soundManager->playSound("death");
				--m_lives;
				player->showDeathIcon();
				std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player);
			}
		}
	}
}
void Gamelogic::checkCollisionsWithRafts(Player* player, SoundManager* soundManager) {
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
	if (player->getPosition().y < 350 && player->getPosition().y > 100 && m_gameActive && !collision) {
		soundManager->playSound("death");
		--m_lives;
		m_gameActive = false;
		player->showDeathIcon();
		std::thread* thread_object = new std::thread(&Gamelogic::makeActive, this, player);
	}
}
void Gamelogic::makeActive(Player* player) {
	std::this_thread::sleep_for(std::chrono::milliseconds(900));
	player->hideDeathIcon();
	player->showPlayer();
	player->setPosition({ Settings::screenWidth / 2, Settings::screenHeight - 25 });
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	m_time = 200;
	m_gameActive = true;
}
void Gamelogic::timerProcess() {
	while (m_time > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		m_time -= 10;
	}
}
int Gamelogic::getLives() {
	return m_lives;
}
int Gamelogic::getScore() {
	return m_score;
}
int Gamelogic::getTime() {
	return m_time;
}
bool Gamelogic::isGameActive() {
	return m_gameActive;
}

void Gamelogic::generateObstacleLines(AssetsManager* assetsManager) {
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
void Gamelogic::generateRaftLines(AssetsManager* assetsManager) {
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
void Gamelogic::generateSafeZones(AssetsManager* assetsManager) {
	for (size_t i = 1; i < 6; i++)
	{
		m_safeZones.push_back(
			new SafeZone{
				200 * (int)i,
				50,
				0,
				1,
				assetsManager->getTexture("player")
			}
		);
	}
}