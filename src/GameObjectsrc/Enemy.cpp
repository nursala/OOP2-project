#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "StatesInc/ChasingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "WorldInc/World.h"
#include <cmath>
#include "WeaponInc/HandGun.h"
#include <limits>

Enemy::Enemy(World& world, const LoadMap& map, const Player& player)
    : Character(world, TextureManager::instance().get(TextureID::Enemy), { 150, 150 }, { 3, 7 }, 0.4f),
    m_playerRef(player)
{
    m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, rand() % 10 + 1);
    m_state = std::make_unique<ChasingState>();
    if (m_state)
        m_state->enter(*this);

    m_attackStrategy = std::make_unique<SimpleShootStrategy>();
    m_weapon = std::make_unique<HandGun>();
    m_speed = m_originalSpeed = 5.f;  // store original speed
    m_armorBar = nullptr;
    m_weapon->getWeaponLight()->setColor(sf::Color::Green);
}

Enemy::~Enemy() {
    if (m_body)
        m_body->GetWorld()->DestroyBody(m_body);
}

bool Enemy::isPlayerVisible() const {
    RayCastClosest raycast;

    b2Vec2 start = { getPosition().x / SCALE, getPosition().y / SCALE };
    sf::Vector2f targetPos = getTarget();
    b2Vec2 end = { targetPos.x / SCALE, targetPos.y / SCALE };

    b2Vec2 delta = end - start;
    if (delta.LengthSquared() < 0.0001f || delta.LengthSquared() > getShootingRange())
        return false;

    m_body->GetWorld()->RayCast(&raycast, start, end);

    return raycast.hit();
}

float Enemy::distanceToPlayer() const {
    sf::Vector2f diff = m_playerRef.getPosition() - getPosition();
    return std::hypot(diff.x, diff.y);
}

void Enemy::fireBullet(const sf::Vector2f&) {
    // if (m_weapon)
    //     m_weapon->shoot(getPosition(), direction);
}

void Enemy::takeDamage(int damage) {
    if (m_health > 0) {
        m_health -= damage;
        if (m_health < 0.f) m_health = 0.f;
    }
    m_healthBar->setValue(m_health);
}

sf::Vector2f Enemy::getTarget() const {
    if (!m_isSpy)
        return m_playerRef.getPosition();

    float minDist = std::numeric_limits<float>::max();
    sf::Vector2f closestEnemyPos = getPosition();

    for (const auto& enemy : m_world.getEnemies()) {
        if (enemy == this || enemy->isSpy())
            continue;

        sf::Vector2f pos = enemy->getPosition();
        float dist = std::hypot(pos.x - getPosition().x, pos.y - getPosition().y);

        if (dist < minDist) {
            minDist = dist;
            closestEnemyPos = pos;
        }
    }

    return closestEnemyPos;
}

void Enemy::update(float deltaTime) {
    Character::update(deltaTime);

    if (m_health <= 0.f) {
        setDestroyed(true);
        return;
    }

    // Handle spy timeout
    if (m_isSpy) {
        m_spyTimer -= deltaTime;
        if (m_spyTimer <= 0.f) {
            m_isSpy = false;
            m_sprite.setColor(sf::Color::White);
        }
    }

    // Handle speed reset
    if (m_speedDownTimer > 0.f) {
        m_speedDownTimer -= deltaTime;
        if (m_speedDownTimer <= 0.f) {
            m_speed = m_originalSpeed;  // reset to normal speed
        }
    }
}

void Enemy::speedDown() {
    m_speed -= 0.5f;
    if (m_speed < 1.f) m_speed = 1.f;
}

void Enemy::setSpeedDownTimer(float seconds) {
    speedDown();               // Apply slow
    m_speedDownTimer = seconds;
}

void Enemy::setSpy(bool value) {
    m_isSpy = value;
    if (m_isSpy)
        m_sprite.setColor(sf::Color::Green);
}

bool Enemy::isSpy() const {
    return m_isSpy;
}

void Enemy::setSpyTimer(float seconds) {
    m_spyTimer = seconds;
}
