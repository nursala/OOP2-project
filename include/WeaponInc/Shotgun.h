#pragma once

#include "WeaponInc/Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun();
	std::vector<std::unique_ptr<Bullet>> fire(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, std::shared_ptr<Character> owner) override;
};

