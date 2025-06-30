#pragma once

class Character;

class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;

    virtual bool attack(Character& character, float deltaTime) = 0;
};