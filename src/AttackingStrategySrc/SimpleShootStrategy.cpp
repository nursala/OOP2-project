#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"
#include "GameObject/Entity.h"
#include "WorldInc/World.h"
#include <iostream>

void SimpleShootStrategy::attack(Character& self, float) {
    auto* weapon = self.getWeapon();
    if (!weapon)
        return;


    Character* targetC = self.getTarget().get();
    sf::Vector2f target;

    if (targetC) {
        target = targetC->getPosition();
    }
    else {
        return; 
    }

    sf::Vector2f direction = target - self.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.f)
        return;

    direction /= length;
    float muzzleOffset = 30.f;
    sf::Vector2f bulletPos = self.getPosition() + direction * muzzleOffset;

    self.getWorld().addBullets(
        weapon->fire(self.getWorld(), bulletPos, direction, self.shared_from_this())
    );
}

