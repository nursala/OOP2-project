#pragma once

class Character;

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;

    virtual void attack(Character& character, float deltaTime) = 0;
};