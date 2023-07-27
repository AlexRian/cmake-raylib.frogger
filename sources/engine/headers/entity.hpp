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
	int m_scale;
	Texture2D* m_texture;

public:
	Entity() 
		: m_position(Vector2{ 0,0 }), m_angle(180) {};
	Entity(int positionX, int positionY, float angle)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle } {};
	Entity(int positionX, int positionY, float angle, int width, int height)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle }, m_width(width), m_height(height) {};
	Entity(int positionX, int positionY, float angle, int scale, Texture2D* texture)
		:m_position{ Vector2{ (float)positionX, (float)positionY } }, m_angle{ angle }, m_scale(scale), m_texture(texture) {};
	
	virtual void draw() {};
	
	Vector2 getPosition();
	Vector2 getSize();

	void setPosition(Vector2 position);
	void setSize(Vector2 size);
};