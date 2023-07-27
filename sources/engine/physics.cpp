#include "headers/physics.hpp"

extern const float SCALE = 30.f;

void Physics::makeWorldStep() {
    if (m_active) {
        m_world.Step(1 / 60.f, 16, 6);
    }
}

void Physics::addPostAction(std::function<void()> func) {
    m_postActions.push_back(func);
}

void Physics::applyActions() {
    for (const auto& func : m_postActions) {
        func();
    }
    m_postActions.clear();
}

void Physics::switchActiveState() {
    m_active = !m_active;
}

b2Body* Physics::getBody(
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
b2World* Physics::getWorld() {
    return &m_world;
}

void PhysicsEntity::applyPhysicsPosition() {
    m_position = Vector2{ (float)m_body->GetPosition().x * SCALE, (float)m_body->GetPosition().y * SCALE };
};

float PhysicsEntity::getBodyAngle() {
    return m_body->GetAngle() * 180 / b2_pi;
}

b2Vec2 PhysicsEntity::getBodyVelocty() {
    return m_body->GetLinearVelocity();
}

b2Body* PhysicsEntity::getBody() {
    return m_body;
}

void PhysicsEntity::switchDynamicState() {
    m_body->GetType() == b2_dynamicBody ? m_body->SetType(b2_staticBody) : m_body->SetType(b2_dynamicBody);
}

void PhysicsEntity::applyForce(b2Vec2 directionVector) {
    m_body->ApplyForce(directionVector, m_body->GetWorldCenter(), true);
}