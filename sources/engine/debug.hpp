#pragma once
#include <vector>
#include <string>
#include "raylib.h"

class Debug
{
private:
	std::vector<std::string> m_messages;
	Vector2 m_position;
	bool m_active;

public:
	Debug(int positionX, int positionY, bool isActive) {
		m_position = Vector2{ (float)positionX, (float)positionY };
		m_active = isActive;
	}

	void draw() {
		if (m_active) {
			DrawRectangle(m_position.x, m_position.y, 150, 250, BLACK);
			if (!m_messages.empty()) {
				for (int i = m_messages.size() - 1; i >= 0; --i) {
					DrawText(m_messages[i].c_str(), m_position.x + 10, m_position.y + i * 20, 20, WHITE);
				}
			}
		}
	};
	void log(std::string message) {
		if (m_messages.size() == 12) {
			m_messages.erase(m_messages.begin());
		}
		m_messages.push_back(message);
	};
};