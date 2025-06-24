#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include <cmath>
#include <algorithm>
#include "GameObject/Character.h"
#include "GameObject/Enemy.h"
#include <random>
#include <iostream>

IQChaseStrategy::IQChaseStrategy(const Player& player, const LoadMap& map, int iqLevel)
    : m_player(player), m_map(map), m_iqLevel(iqLevel), m_pathUpdateTimer(0.f), m_randomDirTimer(0.f),
    m_lastPosition(0.f, 0.f), m_stuckTimer(0.f)
{
}

MoveInfo IQChaseStrategy::move(Character& character, float deltaTime)
{
    sf::Vector2f enemyPos = character.getPosition();
    sf::Vector2f playerPos = m_player.getPosition();

    float distToPlayer = distance(enemyPos, playerPos);
    if (distToPlayer < 150.f && m_iqLevel < 10) ++m_iqLevel;
    if (distToPlayer > 400.f && m_iqLevel > 1) --m_iqLevel;

    float chanceToUseAStar = m_iqLevel / 10.f;
    sf::Vector2f dir;

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.f, 1.f);

    m_pathUpdateTimer += deltaTime;
    m_behaviorLockTimer += deltaTime;

    if (m_behaviorLockTimer >= m_behaviorLockDuration) {
        m_behaviorLockTimer = 0.f;
        m_usingAStar = dist(rng) < chanceToUseAStar;
        /*if (auto self = dynamic_cast<Enemy*>(&character)) {
            if (self->isSpy())
                m_usingAStar = false;
        }*/

        if (m_usingAStar) {
            sf::Vector2i start(static_cast<int>(enemyPos.x / m_map.getTileWidth()), static_cast<int>(enemyPos.y / m_map.getTileHeight()));
            sf::Vector2i goal(static_cast<int>(playerPos.x / m_map.getTileWidth()), static_cast<int>(playerPos.y / m_map.getTileHeight()));

            auto path = AStarPathfinder::findPath(m_map, start, goal);
            if (!path.empty()) {
                m_currentPath = path;
            }
            else {
                m_usingAStar = false;
            }
        }
    }

    if (m_usingAStar && !m_currentPath.empty()) {
        sf::Vector2f nextTileCenter = {
            (m_currentPath[0].x + 0.5f) * m_map.getTileWidth(),
            (m_currentPath[0].y + 0.5f) * m_map.getTileHeight()
        };

        dir = normalize(nextTileCenter - enemyPos);

        if (distance(enemyPos, nextTileCenter) < 5.f)
            m_currentPath.erase(m_currentPath.begin());
    }
    else {
        m_randomDirTimer += deltaTime;
        if (m_randomDirTimer >= m_randomDirDuration) {
            m_randomDirection = generateRandomDirection(character, deltaTime);
            m_randomDirTimer = 0.f;
        }
        dir = m_randomDirection;
    }

    float moved = distance(enemyPos, m_lastPosition);
    if (moved < m_stuckThreshold)
        m_stuckTimer += deltaTime;
    else
        m_stuckTimer = 0.f;

    if (m_stuckTimer > m_stuckTimeLimit) {
        m_randomDirection = generateRandomDirection(character, deltaTime);
        m_randomDirTimer = 0.f;
        m_stuckTimer = 0.f;
        dir = m_randomDirection;
    }

    m_lastPosition = enemyPos;

    if (auto* body = character.getBody()) {
        float speed = character.getSpeed();
        body->SetLinearVelocity(b2Vec2(dir.x * speed, dir.y * speed));
    }

    return {
        2,
        dir.x >= 0,
        dir
    };
}

sf::Vector2f IQChaseStrategy::getPlayerPostion() const
{
    return m_player.getPosition();
}


sf::Vector2f IQChaseStrategy::generateRandomDirection(const Character& enemy, float) {
	float speed = enemy.getSpeed();
    std::vector<sf::Vector2f> dirs = { {speed,0}, {-speed,0}, {0,speed}, {0,-speed} };
    sf::Vector2f lastDir = { 0.f, 0.f };
    dirs.erase(std::remove(dirs.begin(), dirs.end(), lastDir), dirs.end());
    std::shuffle(dirs.begin(), dirs.end(), std::mt19937(std::random_device{}()));
    return normalize(dirs.front());
}

sf::Vector2f IQChaseStrategy::normalize(const sf::Vector2f& v) {
    float length = std::hypot(v.x, v.y);
    return (length == 0.f) ? sf::Vector2f(0.f, 0.f) : sf::Vector2f(v.x / length, v.y / length);
}

float IQChaseStrategy::distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}