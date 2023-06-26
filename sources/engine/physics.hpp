#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <Box2D/Box2D.h>
#include "settings.hpp"
#include "entity.hpp"

extern const float SCALE = 30.f;

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

    void makeWorldStep() {
        if (m_active) {
            m_world.Step(1 / 60.f, 16, 6);
        }
    }

    void addPostAction(std::function<void()> func) {
        m_postActions.push_back(func);
    }

    void applyActions() {
        for (const auto& func : m_postActions) {
            func();
        }
        m_postActions.clear();
    }

    void switchActiveState() {
        m_active = !m_active;
    }

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
    ) {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(positionX / SCALE, positionY / SCALE);
        BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
        BodyDef.angle = angle * b2_pi / 180.0f;
        BodyDef.userData.pointer = reinterpret_cast<uintptr_t>(new std::string(name));
        b2Body* Body = m_world.CreateBody(&BodyDef);

        b2FixtureDef FixtureDef;
        FixtureDef.density = options.density;
        FixtureDef.friction = options.friction;
        FixtureDef.restitution = options.restitution;

        b2PolygonShape polygon;
        b2CircleShape circle;

        if (type == BodyType::Box) {
            polygon.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
            FixtureDef.shape = &polygon;
        }
        else {
            circle.m_radius = (width / 2) / SCALE;
            FixtureDef.shape = &circle;
        }

        Body->CreateFixture(&FixtureDef);
        return Body;
    }
    b2World* getWorld() {
        return &m_world;
    }
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

    void applyPhysicsPosition() {
        m_position = Vector2{ (float)m_body->GetPosition().x * SCALE, (float)m_body->GetPosition().y * SCALE };
    };

    float getBodyAngle() {
        return m_body->GetAngle() * 180 / b2_pi;
    }

    b2Vec2 getBodyVelocty() {
        return m_body->GetLinearVelocity();
    }

    b2Body* getBody() {
        return m_body;
    }

    void switchDynamicState() {
        m_body->GetType() == b2_dynamicBody ? m_body->SetType(b2_staticBody) : m_body->SetType(b2_dynamicBody);
    }

    void applyForce(b2Vec2 directionVector) {
        m_body->ApplyForce(directionVector, m_body->GetWorldCenter(), true);
    }
};