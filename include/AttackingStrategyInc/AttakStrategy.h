#pragma once

class Character;

//======================================================
// Description:This class defines an interface for attack strategies,
//======================================================
class AttackStrategy {
public:
    virtual ~AttackStrategy() = default;

    virtual bool attack(Character& character) = 0;
};