#pragma once
#include "./engine/entity.hpp"
#include "./engine/physics.hpp"

class Player : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        Rectangle destRec = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
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

class Obstacle : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        Rectangle destRec = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
        DrawTexturePro(
            *m_texture,
            sourceRec,
            destRec,
            { (float)m_texture->width / 2, (float)m_texture->height / 2 },
            (float)m_angle,
            WHITE
        );
    }
    void moveLeft() {
        m_position.x -= 1;
        if (m_position.x < 0) {
            m_position = Vector2{Settings::screenWidth, m_position.y};
        }
    }
    void moveRight() {
        if (m_position.x > Settings::screenWidth) {
            m_position = Vector2{ 0, m_position.y };
        }
        m_position.x += 1;
    }
};

class Raft : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        Rectangle destRec = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
        DrawTexturePro(
            *m_texture,
            sourceRec,
            destRec,
            { (float)m_texture->width / 2, (float)m_texture->height / 2 },
            (float)m_angle,
            WHITE
        );
    }
    void moveLeft() {
        m_position.x -= 1;
        if (m_position.x < 0) {
            m_position = Vector2{ Settings::screenWidth, m_position.y };
        }
    }
    void moveRight() {
        if (m_position.x > Settings::screenWidth) {
            m_position = Vector2{ 0, m_position.y };
        }
        m_position.x += 1;
    }
};

class RaftLine {
public:
    RaftLine(int positionY, int direction, Texture2D* texture)
        : m_positionY(positionY), m_direction(direction)
    {
        for (int i = 1; i < 5; i++)
        {
            Raft obstacle{ (Settings::screenWidth / 4) * i, m_positionY, 0, 1, texture };
            m_obstacles.push_back(obstacle);
        }
    };
    void draw() {
        for (Raft& obstacle : m_obstacles) {
            m_direction > 0 ? obstacle.moveRight() : obstacle.moveLeft();
            obstacle.draw();
        }
    }
private:
    std::vector<Raft> m_obstacles;
    int m_positionY;
    int m_direction;
};

class ObstacleLine {
public:
    ObstacleLine(int positionY, int direction, Texture2D* texture)
        : m_positionY(positionY), m_direction(direction)
    {
        for (int i = 1; i < 5; i++)
        {
            Obstacle obstacle{ (Settings::screenWidth / 4) * i, m_positionY, 0, 1, texture };
            m_obstacles.push_back(obstacle);
        }
    };
    void draw() {
        for (Obstacle& obstacle : m_obstacles) {
            m_direction > 0 ? obstacle.moveRight() : obstacle.moveLeft();
            obstacle.draw();
        }
    }
private:
    std::vector<Obstacle> m_obstacles;
    int m_positionY;
    int m_direction;
};

class Ground : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
        DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, BLACK);
    }
};

class Grass : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
        DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, GREEN);
    }
};

class Water : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
        DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, BLUE);
    }
};