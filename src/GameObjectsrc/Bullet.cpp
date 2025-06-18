#include "GameObject/Bullet.h"
#include <Box2D/Box2D.h>
#include "WorldInc/World.h"

Bullet::Bullet(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
    : Entity()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.gravityScale = 0.f;

    b2Body* body = world.getWorld().CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 4.f / SCALE;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution = 0.f;
    fixtureDef.isSensor = true;

    body->CreateFixture(&fixtureDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    m_body = body;

    m_shape.setRadius(4.f);
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setOrigin(4.f, 4.f);
    m_shape.setPosition(position);
}

void Bullet::update(float deltaTime)
{
    b2Vec2 velocity(m_direction.x * m_speed, m_direction.y * m_speed);
    m_body->SetLinearVelocity(velocity);

    auto pos = m_body->GetPosition();
    m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);

    m_lifetime += deltaTime;
    if (m_lifetime > MAX_LIFETIME)
        m_destroy = true;
}

//void Bullet::handleCollision(Entity& other)
//{
//    m_destroy = true;
//}

bool Bullet::shouldDestroy() const
{
    return m_destroy;
}
