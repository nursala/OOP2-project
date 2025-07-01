#pragma once

class Character;

class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    virtual void move(Character& character, float deltaTime) = 0;
};