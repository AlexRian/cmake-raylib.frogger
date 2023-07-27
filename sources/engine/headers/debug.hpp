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
	Debug(int positionX, int positionY, bool isActive);

	void draw();
	void log(std::string message);
};