#pragma once

#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "LoadMap.h"
#include "GameObject/Player.h"
#include "AStarPathfinder.h"
#include <SFML/System.hpp>
#include <vector>

class IQChaseStrategy : public MoveStrategy {
public:
    IQChaseStrategy(const Player& player, const LoadMap& map, int iqLevel);

    MoveInfo move(Character& character, float deltaTime) override;
    sf::Vector2f getPlayerPostion() const;

private:
    const Player& m_player;
    const LoadMap& m_map;
    int m_iqLevel;

    std::vector<sf::Vector2i> m_currentPath;
    float m_pathUpdateTimer = 0.f;
    float m_randomDirTimer = 0.f;

    const float m_pathUpdateInterval = 0.5f;
    const float m_randomDirDuration = 2.f;
    sf::Vector2f m_randomDirection;

    float m_behaviorLockTimer = 0.f;
    const float m_behaviorLockDuration = 0.5f;
    bool m_usingAStar = false;

    sf::Vector2f m_lastPosition;
    float m_stuckTimer = 0.f;
    const float m_stuckThreshold = 1.0f;
    const float m_stuckTimeLimit = 0.1f;

    sf::Vector2f generateRandomDirection(const Character& enemy, float deltaTime);
    sf::Vector2f normalize(const sf::Vector2f& v);
    float distance(const sf::Vector2f& a, const sf::Vector2f& b);
};