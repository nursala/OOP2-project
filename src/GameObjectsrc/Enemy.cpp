#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "StatesInc/ChasingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "WorldInc/World.h"
#include <cmath>
#include "WeponInc/Gun.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"

Enemy::Enemy(World& world, const LoadMap& map, const Player& player, int iq)
    : Character(world, TextureManager::instance().get(TextureID::Enemy), { 150, 150}, { 5, 5 }, 0.4f),
    m_playerRef(player)
   
{
    m_visable = true;
    m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, iq);
    m_state = std::make_unique<ChasingState>();
    if (m_state)
        m_state->enter(*this);

	m_attackStrategy = std::make_unique<SimpleShootStrategy>();
    m_weapon = std::make_unique<Gun>();
    m_speed = 2.f;
}

Enemy::~Enemy() {
    if (m_body)
        m_body->GetWorld()->DestroyBody(m_body);
}

bool Enemy::isPlayerVisible() const {
    RayCastClosest raycast;

    b2Vec2 start = { getPosition().x / SCALE, getPosition().y / SCALE };
    b2Vec2 end = { m_playerRef.getPosition().x / SCALE, m_playerRef.getPosition().y / SCALE };

    b2Vec2 delta = end - start;
    if (delta.LengthSquared() < 0.0001f)
        return false;

    m_body->GetWorld()->RayCast(&raycast, start, end);

    return raycast.hit() && raycast.getBody() == m_playerRef.getBody();
}

float Enemy::distanceToPlayer() const 
{
    sf::Vector2f diff = m_playerRef.getPosition() - getPosition();
    return std::hypot(diff.x, diff.y);
}

sf::Vector2f Enemy::getTarget() const
{
    return m_playerRef.getPosition();
}

