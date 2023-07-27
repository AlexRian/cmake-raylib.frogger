#include <Box2D/Box2D.h>
#include "headers/entity.hpp"

Vector2 Entity::getPosition() {
	return m_position;
}

void Entity::setPosition(Vector2 position) {
	m_position = position;
}

void Entity::setSize(Vector2 size) {
	m_width = size.x;
	m_height = size.y;
}

Vector2 Entity::getSize() {
	return Vector2{ (float)m_width, (float)m_height };
}