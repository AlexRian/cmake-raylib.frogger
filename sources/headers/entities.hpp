#pragma once
#include "./engine/headers/entity.hpp"
#include "./engine/headers/physics.hpp"

class Player : public Entity {
    using Entity::Entity;
public:
    Player(int positionX, int positionY, float angle, int scale, Texture2D* texture, Texture2D* deathTexture)
        : Entity(positionX, positionY, angle, scale, texture), m_mainTexture{ texture }, m_deathTexture{ deathTexture } {};
    
    void draw();
    void moveUp();
    void moveDown();
    void moveLeft(int stepWidth);
    void moveRight(int stepWidth);
    void showDeathIcon();
    void hideDeathIcon();
    void hidePlayer();
    void showPlayer();
    Rectangle getBody();
private:
    Rectangle m_body;
    Texture2D* m_mainTexture;
    Texture2D* m_deathTexture;
    bool m_hidden = false;
};

class SafeZone : public Entity {
    using Entity::Entity;
public:
    SafeZone(int positionX, int positionY, float angle, int scale, Texture2D* texture)
        : Entity(positionX, positionY, angle, scale, texture), m_playerTexture{ texture } {};
    void draw();
    Rectangle getBody();
    void makeOccupied();
    bool isOccupied();
private:
    Rectangle m_body;
    Texture2D* m_playerTexture;
    bool m_occupied = false;
};

class Obstacle : public Entity {
    using Entity::Entity;
public:
    void draw();
    void moveLeft(int speed);
    void moveRight(int speed);
    Rectangle getBody();
private:
    Rectangle m_body;
};

class Raft : public Entity {
    using Entity::Entity;
public:
    void draw();
    void moveLeft(int speed);
    void moveRight(int speed);
    Rectangle getBody();
private:
    Rectangle m_body;
};

class RaftLine {
public:
    RaftLine(int positionY, int direction, Texture2D* texture, int speed);

    void makeMove();
    void draw();
    int getDirection();
    std::vector<Raft*> getRafts();
    int getSpeed();
private:
    std::vector<Raft*> m_rafts;
    int m_positionY;
    int m_direction;
    int m_speed;
};

class ObstacleLine {
public:
    ObstacleLine(int positionY, int direction, Texture2D* texture, int speed);
    
    void makeMove();
    void draw();
    std::vector<Obstacle*> getObstacles();
private:
    std::vector<Obstacle*> m_obstacles;
    int m_positionY;
    int m_direction;
    int m_speed;
};

class Ground : public Entity {
    using Entity::Entity;
public:
    void draw();
};

class Grass : public Entity {
    using Entity::Entity;
public:
    void draw();
};

class Water : public Entity {
    using Entity::Entity;
public:
    void draw();
};