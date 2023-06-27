#include "./engine/entity.hpp"
#include "./engine/physics.hpp"

class Player : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        Rectangle destRec = { m_position.x, m_position.y, m_width, m_height};
        DrawTexturePro(
            *m_texture, 
            sourceRec, 
            destRec, 
            { (float)m_texture->width / 2, (float)m_texture->height / 2 }, 
            (float)m_angle, 
            WHITE
        );
    }
    void moveUp() {
        m_position.y -= Settings::playerStepWidth;
    }
    void moveLeft() {
        m_position.x -= Settings::playerStepWidth;
    }
    void moveDown() {
        m_position.y += Settings::playerStepWidth;
    }
    void moveRight() {
        m_position.x += Settings::playerStepWidth;
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