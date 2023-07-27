#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <Box2D/Box2D.h>
#include "./headers/settings.hpp"
#include "entity.hpp"

enum BodyType {
    Box,
    Circle,
};

struct BodyOptions
{
    BodyOptions(float desnity, float friction, float restitution) :density(desnity), friction(friction), restitution(restitution){}
    float density;
    float friction;
    float restitution;
};

class Physics {
private:
	b2Vec2 m_gravity;
	b2World m_world;
    std::vector<b2Body*> m_bodies;
    bool m_active = true;
    std::vector<std::function<void()>> m_postActions;
public:
    Physics(b2Vec2 gravity = b2Vec2({0,0}))
        :m_gravity{ gravity }, m_world{ gravity } {};

    void makeWorldStep();
    void addPostAction(std::function<void()> func);
    void applyActions();
    void switchActiveState();
    b2Body* getBody(
        char* name,
        int positionX,
        int positionY,
        float angle,
        int width,
        int height,
        bool dynamic,
        BodyType type,
        BodyOptions options
    );
    b2World* getWorld();
};

class PhysicsEntity : public Entity
{
    using Entity::Entity;

protected:
    b2Body* m_body;

public:
    PhysicsEntity(int positionX, int positionY, float angle, b2Body* body)
        : Entity(positionX, positionY, angle), m_body{ body } {};

    PhysicsEntity(int positionX, int positionY, float angle, int width, int height, b2Body* body)
        : Entity(positionX, positionY, angle, width, height), m_body{ body } {};

    void applyPhysicsPosition();
    float getBodyAngle();
    b2Vec2 getBodyVelocty();
    b2Body* getBody();
    void switchDynamicState();
    void applyForce(b2Vec2 directionVector);
};