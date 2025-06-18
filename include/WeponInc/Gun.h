#pragma once

#include "WeponInc/Weapon.h"
class World;

class Gun : public Weapon {
public:
    Gun();

    void fire(World& world, const sf::Vector2f& position, const sf::Vector2f& direction) override;
private:
};

