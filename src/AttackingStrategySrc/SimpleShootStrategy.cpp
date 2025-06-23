#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "GameObject/Character.h"
#include "WeponInc/Weapon.h"
#include "GameObject/Entity.h"
#include "WorldInc/World.h"
#include <iostream>

void SimpleShootStrategy::attack(Character& self, float dt) {

    auto* weapon = self.getWeapon();
    if (!weapon)
        return;

    sf::Vector2f target = self.getTarget();

    sf::Vector2f direction = target - self.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;
	self.getWorld().addBullet(weapon->fire(self.getWorld(), self.getPosition(), direction,&self));
}

