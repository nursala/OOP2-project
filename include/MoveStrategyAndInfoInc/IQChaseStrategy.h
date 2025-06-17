#pragma once
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "GameObject/Player.h"
#include <random>
#include <SFML/Graphics.hpp>

class IQChaseStrategy : public MoveStrategy {
public:
    IQChaseStrategy(const Player& player, int iqLevel = 3);
    virtual MoveInfo move(Entity& enemy, float deltaTime) override;

private:
    const Player& m_player;
    int m_iqLevel;
    int m_goodSteps = 0;
    sf::Vector2f m_lastDirection = { 0, 0 };
    float m_timeSinceLastDirectionChange = 0.f;
    const float m_directionChangeInterval = 0.1f; 

    sf::Vector2f calculateSmartDirection(const Entity& enemy, float deltaTime);
    sf::Vector2f generateRandomDirection(const Entity& enemy, float deltaTime);
};