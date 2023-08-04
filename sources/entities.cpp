#include "headers/entities.hpp"

//Player
void Player::draw() {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
    m_body = { m_position.x, m_position.y, (float)m_texture->width * m_scale, (float)m_texture->height * m_scale };
    if (!m_hidden) {
        DrawTexturePro(
            *m_texture,
            sourceRec,
            m_body,
            { (float)m_texture->width / 2, (float)m_texture->height / 2 },
            (float)m_angle,
            WHITE
        );
    }
}
void Player::moveUp() {
    m_position.y -= Settings::playerStepWidth;
}
void Player::moveDown() {
    m_position.y += Settings::playerStepWidth;
}
void Player::moveLeft(int stepWidth) {
    m_position.x -= stepWidth;
}
void Player::moveRight(int stepWidth) {
    m_position.x += stepWidth;
}
void Player::showDeathIcon() {
    m_texture = m_deathTexture;
}
void Player::hideDeathIcon() {
    m_texture = m_mainTexture;
}
void Player::hidePlayer() {
    m_hidden = true;
}
void Player::showPlayer() {
    m_hidden = false;
}
Rectangle Player::getBody() {
    return m_body;
}

//SafeZone
void SafeZone::draw() {
    DrawRectangle(m_position.x, m_position.y, 50, 50, BLUE);
    Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };
    m_body = { m_position.x, m_position.y, 50, 50 };
    if (m_occupied) {
        DrawTexturePro(
            *m_texture,
            sourceRec,
            { m_position.x, m_position.y, (float)m_texture->width, (float)m_texture->height },
            { 0, 0 },
            (float)m_angle,
            WHITE
        );
    }
}
Rectangle SafeZone::getBody() {
    return m_body;
}
void SafeZone::makeOccupied() {
    m_occupied = true;
}
bool SafeZone::isOccupied() {
    return m_occupied;
}

//Obstacle
void Obstacle::draw() {
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
void Obstacle::moveLeft(int speed) {
    m_position.x -= speed;
    if (m_position.x < 0) {
        m_position = Vector2{ Settings::screenWidth, m_position.y };
    }
}
void Obstacle::moveRight(int speed) {
    if (m_position.x > Settings::screenWidth) {
        m_position = Vector2{ 0, m_position.y };
    }
    m_position.x += speed;
}
Rectangle Obstacle::getBody() {
    return m_body;
}

//Raft
void Raft::draw() {
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
void Raft::moveLeft(int speed) {
    m_position.x -= speed;
    if (m_position.x < 0) {
        m_position = Vector2{ Settings::screenWidth, m_position.y };
    }
}
void Raft::moveRight(int speed) {
    if (m_position.x > Settings::screenWidth) {
        m_position = Vector2{ 0, m_position.y };
    }
    m_position.x += speed;
}
Rectangle Raft::getBody() {
    return m_body;
}

//RaftLine
RaftLine::RaftLine(int positionY, int direction, Texture2D* texture, int speed)
    : m_positionY(positionY), m_direction(direction), m_speed(speed)
{
    for (int i = 1; i < 5; i++)
    {
        Raft* obstacle = new Raft((Settings::screenWidth / 2) * i, m_positionY, 0, 1, texture);
        m_rafts.push_back(obstacle);
    }
};
void RaftLine::makeMove() {
    for (Raft* obstacle : m_rafts) {
        m_direction > 0 ? obstacle->moveRight(m_speed) : obstacle->moveLeft(m_speed);
    }
}
void RaftLine::draw() {
    for (Raft* obstacle : m_rafts) {
        obstacle->draw();
    }
}
int RaftLine::getDirection() {
    return m_direction;
}
int RaftLine::getSpeed() {
    return m_speed;
}
std::vector<Raft*> RaftLine::getRafts() {
    return m_rafts;
}

//ObstacleLine
ObstacleLine::ObstacleLine(int positionY, int direction, Texture2D * texture, int speed)
    : m_positionY(positionY), m_direction(direction), m_speed(speed)
{
    for (int i = 1; i < 5; i++)
    {

        Obstacle* obstacle = new Obstacle{ (Settings::screenWidth / 4) * i, m_positionY, 0, 1, texture };
        m_obstacles.push_back(obstacle);
    }
};
void ObstacleLine::makeMove() {
    for (Obstacle* obstacle : m_obstacles) {
        m_direction > 0 ? obstacle->moveRight(m_speed) : obstacle->moveLeft(m_speed);
    }
}
void ObstacleLine::draw() {
    for (Obstacle* obstacle : m_obstacles) {
        obstacle->draw();
    }
}
std::vector<Obstacle*> ObstacleLine::getObstacles() {
    return m_obstacles;
}

//Ground
void Ground::draw() {
    Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
    DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, BLACK);
}

//Grass
void Grass::draw() {
    Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
    DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, GREEN);
}

//Water
void Water::draw() {
    Rectangle rec = { m_position.x, m_position.y, Settings::screenWidth, m_height };
    DrawRectanglePro(rec, { Settings::screenWidth / 2, (float)m_height / 2 }, m_angle, BLUE);
}