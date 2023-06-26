#pragma once
#include <Box2D/Box2D.h>
#include "raylib.h"

class Entity
{
protected:
	Vector2 m_position;
	float m_angle;
	int m_width;
	int m_height;
	Texture2D* m_texture;

public:
	Entity() 
		: m_position(Vector2{ 0,0 }), m_angle(180) {};
	Entity(int positionX, int positionY, float angle)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle } {};
	Entity(int positionX, int positionY, float angle, int width, int height)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle }, m_width(width), m_height(height) {};
	Entity(int positionX, int positionY, float angle, int width, int height, Texture2D* texture)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle }, m_width(width), m_height(height), m_texture(texture) {};
	virtual void draw() {};
	Vector2 getPosition() {
		return m_position;
	};
	void setPosition(Vector2 position) {
		m_position = position;
	};
	void setSize(Vector2 size) {
		m_width = size.x;
		m_height = size.y;
	}
	Vector2 getSize() {
		return Vector2{ (float)m_width, (float)m_height };
	}
};