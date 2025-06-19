#include "GameObject/Bullet.h"
#include <Box2D/Box2D.h>
#include "WorldInc/World.h"

Bullet::Bullet(World& world, const sf::Vector2f& position, const sf::Vector2f& direction)
	: Entity(world, nullptr, position, { 1, 1 }, 0.1f),
	m_direction(direction),
	m_speed(10.f)
{
    m_shape.setRadius(4.f);
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setOrigin(4.f, 4.f);
    m_shape.setPosition(position);
}

void Bullet::customizeBodyDef(b2BodyDef& bodyDef)
{
	bodyDef.bullet = true; // Set as a bullet to avoid tunneling
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
