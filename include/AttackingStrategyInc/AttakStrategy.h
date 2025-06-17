#pragma once

class Enemy;

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;

    virtual void attack(Enemy& enemy, float deltaTime) = 0;
};