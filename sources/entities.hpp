#include "./engine/entity.hpp"
#include "./engine/physics.hpp"

class Shape : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 120, 60 };
        DrawRectanglePro(rec, { 60, 30 }, m_angle, RED);
    }
};

class Block : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 200, 120 };
        DrawRectanglePro(rec, { 100, 60 }, getBodyAngle(), RED);
    }
};

class Ground : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, 60 };
        DrawRectanglePro(rec, { Settings::screenWidth / 2, 30 }, getBodyAngle(), BLACK);
    }
};