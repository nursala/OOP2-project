//==============================================
// File: Character.cpp
// Description: Implementation of the base Character class.
//==============================================

#include "GameObject/Character.h"
#include "WorldInc/World.h"
#include "VisionLight.h"
#include "WeaponInc/Weapon.h"
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Shotgun.h"
#include "WeaponInc/Sniper.h"
#include "ResourseInc/SoundManager.h"
#include "StatesInc/WalkingState.h"
#include "StatesInc/AttackingState.h"
#include "ResourseInc/TextureManager.h"

#include <iostream>
#include <cmath>

//=============================
// Constructor
//=============================
Character::Character(World& world, const b2Vec2& positionB2)
    : Entity(world, positionB2)
{
    m_visionLight = std::make_unique<VisionLight>(300.f, 60.f); // Default range and beam angle
    m_visionLight->setIntensity(0.1f);                          // Light intensity
    m_visionLight->setScale(1.2f, 1.2f);

    m_healthBar = std::make_unique<HealthBar>(50.f, 5.f, 100);
}

//=============================
// update()
// Handles AI, movement, weapon, animation, health bar, and light
//=============================
void Character::update(float deltaTime)
{
    updateTargets();
    getClosestTarget(); // to be implemented by derived class

    // Handle state logic
    if (m_state) {
        auto newState = m_state->handleInput(*this);
        if (newState && m_state.get() != newState.get()) {
            m_state = std::move(newState);
        }
        m_state->update(*this, deltaTime);
    }

    // Update weapon
    if (m_weapon)
        m_weapon->update(getPosition(), getBody()->GetAngle(), deltaTime);

    // Update animation frame
    m_sprite.setPosition(getPosition());
    m_sprite.setTextureRect(m_animation->getUvRect());

    // Update health bar
    sf::Vector2f healthBarPos = { getPosition().x , getPosition().y + 40 };
    m_healthBar->setPosition(healthBarPos);
    m_healthBar->setValue(m_health);

    // Update vision light
    if (m_visionLight)
        m_visionLight->update(getPosition(), getBody()->GetAngle() / 30.f);

    // Cast lights
    auto& CloseEdges = m_world.getCloseEdges();
    if (m_weapon && m_weapon->getWeaponLight())
        m_weapon->getWeaponLight()->castLight(CloseEdges.begin(), CloseEdges.end());

    if (m_visionLight)
        m_visionLight->castLight(CloseEdges.begin(), CloseEdges.end());
}

//=============================
// render()
// Renders sprite, health bar, lights, and weapon
//=============================
void Character::render(RenderLayers& renderLayers)
{
    if (m_visable)
    {
        renderLayers.drawForeground(m_sprite);
        m_healthBar->draw(renderLayers);

        if (m_visionLight) {
            renderLayers.drawLight(*m_visionLight);
            renderLayers.drawForeground(*m_visionLight);
        }

        if (m_weapon)
            m_weapon->draw(renderLayers);
    }
    else {
        renderLayers.drawBackground(m_sprite);
    }
}

//=============================
// getBodyType()
// Returns Box2D body type for character
//=============================
b2BodyType Character::getBodyType() const
{
    return b2_dynamicBody;
}

//=============================
// move()
// Applies movement strategy and sets animation accordingly
//=============================
void Character::move(float dt)
{
    if (m_moveStrategy)
    {
        m_moveStrategy->move(*this, dt);

        
    }
}

//=============================
// getWeapon()
//=============================
Weapon* Character::getWeapon()
{
    return m_weapon.get();
}

//=============================
// shoot()
// Triggers attack strategy and sound
//=============================
void Character::shoot()
{
    if (m_attackStrategy && m_weapon->getFireTimer() <= 0.f)
    {
        if (!m_attackStrategy->attack(*this)) return;

        SoundManager::instance().play(Constants::WeaponDataMap.at(m_weapon->getType()).shootSound);
        SoundManager::instance().setVolume(Constants::WeaponDataMap.at(m_weapon->getType()).shootSound, 80.f);
    }
}

//=============================
// getShootingRange()
//=============================
float Character::getShootingRange() const
{
    return m_weapon ? m_weapon->getShootingRange() : 0.f;
}

//=============================
// setShootingRange()
//=============================
void Character::setShootingRange(const float range)
{
    if (m_weapon)
        m_weapon->setShootingRange(range);
}

//=============================
// setRotation()
// Sets rotation of body and sprite
//=============================
void Character::setRotation(const float angle)
{
    if (m_body)
    {
        m_body->SetTransform(b2Vec2(getPosition().x / SCALE, getPosition().y / SCALE), angle * SCALE);
        m_sprite.setRotation(angle);
    }
}

//=============================
// updateTargets()
// Casts rays in vision cone and collects fixtures
//=============================
void Character::updateTargets()
{
    m_hitFixtures.clear();
    if (!m_weapon->getWeaponLight()) return;

    float startAngle = m_weapon->getWeaponLight()->getRotation() - m_weapon->getWeaponLight()->getBeamAngle() / 2.f;
    float endAngle = m_weapon->getWeaponLight()->getRotation() + m_weapon->getWeaponLight()->getBeamAngle() / 2.f;
    const int rayCount = 36;
    float angleStep = (endAngle - startAngle) / static_cast<float>(rayCount);

    sf::Vector2f lightPos = m_weapon->getWeaponLight()->getPosition();
    b2Vec2 origin(lightPos.x / 30.f, lightPos.y / 30.f);

    for (int i = 0; i <= rayCount; ++i)
    {
        float angleDeg = startAngle + i * angleStep;
        float angleRad = angleDeg * b2_pi / 180.f;
        b2Vec2 direction(std::cos(angleRad), std::sin(angleRad));
        b2Vec2 endPoint = origin + (m_weapon->getWeaponLight()->getRange() / 30.f) * direction;

        RayCastClosest callback;
        m_world.getWorld().RayCast(&callback, origin, endPoint);

        if (callback.hit() && callback.getFixture())
        {
            b2Body* body = callback.getFixture()->GetBody();
            if (body->GetType() == b2_dynamicBody && body != m_body)
                m_hitFixtures.insert(callback.getFixture());
        }
    }
}
