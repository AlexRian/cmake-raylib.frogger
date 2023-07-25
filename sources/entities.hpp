#pragma once
#include "./engine/entity.hpp"
#include "./engine/physics.hpp"

class Player : public Entity {
    using Entity::Entity;
public:
    Player(int positionX, int positionY, float angle, int scale, Texture2D* texture, Texture2D* deathTexture)
        : Entity(positionX, positionY, angle, scale, texture), m_mainTexture{ texture }, m_deathTexture{ deathTexture } {};
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        m_body = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
        DrawTexturePro(
            *m_texture, 
            sourceRec, 
            m_body,
            { (float)m_texture->width / 2, (float)m_texture->height / 2 }, 
            (float)m_angle, 
            WHITE
        );
    }
    void moveUp() {
        m_position.y -= Settings::playerStepWidth;
    }
    void moveDown() {
        m_position.y += Settings::playerStepWidth;
    }
    void moveLeft(int stepWidth) {
        m_position.x -= stepWidth;
    }
    void moveRight(int stepWidth) {
        m_position.x += stepWidth;
    }
    void showDeathIcon() {
        m_texture = m_deathTexture;
    }
    void hideDeathIcon() {
        m_texture = m_mainTexture;
    }
    Rectangle getBody() {
        return m_body;
    }
private:
    Rectangle m_body;
    Texture2D* m_mainTexture;
    Texture2D* m_deathTexture;
};

class Obstacle : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        m_body = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
        DrawTexturePro(
            *m_texture,
            sourceRec,
            m_body,
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
    Rectangle getBody() {
        return m_body;
    }
private:
    Rectangle m_body;
};

class Raft : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
        m_body = { m_position.x, m_position.y, (float)m_texture->width * m_scale - 50, (float)m_texture->height * m_scale };
        DrawTexturePro(
            *m_texture,
            sourceRec,
            m_body,
            { (float)m_texture->width / 2 - 100, (float)m_texture->height / 2 },
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
    Rectangle getBody() {
        return m_body;
    }
private:
    Rectangle m_body;
};

class RaftLine {
public:
    RaftLine(int positionY, int direction, Texture2D* texture)
        : m_positionY(positionY), m_direction(direction)
    {
        for (int i = 1; i < 5; i++)
        {
            Raft* obstacle = new Raft((Settings::screenWidth / 2) * i, m_positionY, 0, 1, texture);
            m_rafts.push_back(obstacle);
        }
    };
    void makeMove() {
        for (Raft* obstacle : m_rafts) {
            m_direction > 0 ? obstacle->moveRight() : obstacle->moveLeft();
        }
    }
    void draw() {
        for (Raft* obstacle : m_rafts) {
            obstacle->draw();
        }
    }
    int getDirection() {
        return m_direction;
    }
    std::vector<Raft*> getRafts() {
        return m_rafts;
    }
private:
    std::vector<Raft*> m_rafts;
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

            Obstacle* obstacle = new Obstacle{ (Settings::screenWidth / 4) * i, m_positionY, 0, 1, texture };
            m_obstacles.push_back(obstacle);
        }
    };
    void makeMove() {
        for (Obstacle* obstacle : m_obstacles) {
            m_direction > 0 ? obstacle->moveRight() : obstacle->moveLeft();
        }
    }
    void draw() {
        for (Obstacle* obstacle : m_obstacles) {
            obstacle->draw();
        }
    }
    std::vector<Obstacle*> getObstacles() {
        return m_obstacles;
    }
private:
    std::vector<Obstacle*> m_obstacles;
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