#include "GameObject/Bullet.h"
#include <Box2D/Box2D.h>
#include "WorldInc/World.h"
#include "ResourseInc/TextureManager.h"
#include <cmath>
#include <iostream>

Bullet::Bullet(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner, float damage, float range)
    : Entity(world, TextureManager::instance().get(TextureID::BULLET), position, { 1, 1 }, 0.1f),
    m_direction(direction), m_owner(owner)
{
    m_visable = true;
    m_speed = 15.f;
	m_bodyRadius = 0.3f; // Set a small radius for the bullet
    m_damage = damage;
	m_range = range + 10.f;
}

void Bullet::customizeBodyDef(b2BodyDef& bodyDef)
{
    bodyDef.bullet = true; 
}

void Bullet::customizeFixtureDef(b2FixtureDef& fixtureDef)
{
    fixtureDef.isSensor = true; 
}

b2BodyType Bullet::getBodyType() const
{
    return b2_kinematicBody; 
}

void Bullet::update(float deltaTime)
{
    if (!m_body || m_destroy) return;

    b2Vec2 velocity(m_direction.x * m_speed, m_direction.y * m_speed);
    m_body->SetLinearVelocity(velocity);

    b2Vec2 pos = m_body->GetPosition();
    m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	m_position = { pos.x * SCALE, pos.y * SCALE };

    //m_lifetime += deltaTime;
    float dx = m_position.x - m_initialPosition.x;
    float dy = m_position.y - m_initialPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance > m_range)
        m_destroy = true;
}

bool Bullet::shouldDestroy() const
{
    return m_destroy;
}

Character* Bullet::getOwner() const
{
    return m_owner->isDestroyed() ? nullptr : m_owner;
}

float Bullet::getDamage() const
{
    return m_damage;
}

void Bullet::setDamage(float damage)
{
    m_damage = damage;
}