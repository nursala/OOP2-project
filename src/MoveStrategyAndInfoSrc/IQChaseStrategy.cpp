#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include <cmath>
#include <algorithm>
#include "GameObject/Entity.h"

IQChaseStrategy::IQChaseStrategy(const Player& player, int iqLevel)
    : m_player(player), m_iqLevel(iqLevel) {
}

MoveInfo IQChaseStrategy::move(Entity& entity, float deltaTime) {
    auto* body = entity.getBody();
    if (!body) return {};

    sf::Vector2f dir = m_lastDirection;

    m_timeSinceLastDirectionChange += deltaTime;

    if (m_timeSinceLastDirectionChange >= m_directionChangeInterval) {
        if (m_goodSteps < m_iqLevel && entity.getDirection() == m_lastDirection) {
            dir = calculateSmartDirection(entity, deltaTime);
        }
        else {
            dir = generateRandomDirection(entity, deltaTime);
        }

        m_goodSteps = (m_goodSteps + 1) % 10;
        m_lastDirection = dir;
        m_timeSinceLastDirectionChange = 0.f; 
    }

    b2Vec2 velocity(dir.x, dir.y);
    body->SetLinearVelocity(velocity);

    MoveInfo info;
    info.row = (velocity.Length() > 0.1f) ? 2 : 1;
    info.faceRight = velocity.x >= 0;
    info.direction = dir;

    return info;
}

sf::Vector2f IQChaseStrategy::calculateSmartDirection(const Entity& enemy, float deltaTime) {
    sf::Vector2f toPlayer = m_player.getPixels() - enemy.getPixels();
    std::vector<sf::Vector2f> directions = { {5,0}, {-5,0}, {0,5}, {0,-5} };

    float minDist = FLT_MAX;
    sf::Vector2f bestDir = { 0, 0 };

    for (const auto& dir : directions) {
        if (dir == -enemy.getLastMoveInfo().direction)
            continue;

        sf::Vector2f testPos = enemy.getPixels() + dir * deltaTime;
        float dist = std::hypot(m_player.getPixels().x - testPos.x, m_player.getPixels().y - testPos.y);

        if (dist < minDist) {
            minDist = dist;
            bestDir = dir;
        }
    }
    return bestDir;
}

sf::Vector2f IQChaseStrategy::generateRandomDirection(const Entity& enemy, float deltaTime) {
    std::vector<sf::Vector2f> dirs = { {2,0}, {-2,0}, {0,2}, {0,-2} };
    sf::Vector2f lastDir = enemy.getLastMoveInfo().direction;

    dirs.erase(std::remove(dirs.begin(), dirs.end(), -lastDir), dirs.end());

    std::shuffle(dirs.begin(), dirs.end(), std::mt19937(std::random_device{}()));

    return dirs.front(); 
}
