#pragma once

#include "WeaponInc/Weapon.h"

class Shotgun : public Weapon
{
public:
	Shotgun();
	virtual std::vector<std::unique_ptr<Bullet>> fire(World& world, b2Vec2& position,
		const sf::Vector2f& direction, std::shared_ptr<Character> owner) override;
};
