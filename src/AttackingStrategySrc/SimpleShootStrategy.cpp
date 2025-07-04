#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"
#include "GameObject/Entity.h"
#include "WorldInc/World.h"
#include "ResourseInc/TextureManager.h"
#include <iostream>
#include <cmath>

// Implements the simple shooting behavior:
// If the character has a weapon and a visible target, it fires a bullet toward the target.
bool SimpleShootStrategy::attack(Character& self) {
    // Get weapon; return false if none.
    Weapon* weapon = self.getWeapon();
    if (!weapon)
        return false;

    // Get target using weak_ptr; return false if target is null.
    Character* targetC = self.getTarget().get();
    if (!targetC)
        return false;

    // Compute direction vector from self to target.
    const sf::Vector2f targetPos = targetC->getPosition();
    sf::Vector2f direction = targetPos - self.getPosition();
    const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length == 0.f)
        return false;

    // Normalize the direction vector.
    direction /= length;

    // Apply an offset from the muzzle to avoid spawning the bullet inside the player.
    constexpr float muzzleOffset = 50.f;
    const sf::Vector2f bulletPos = self.getPosition() + direction * muzzleOffset;
    const b2Vec2 bulletPosB2(bulletPos.x, bulletPos.y);

    // Fire the weapon and pass the bullet(s) to the world.
    self.getWorld().addBullets(
        weapon->fire(self.getWorld(), bulletPosB2, direction, self.shared_from_this())
    );

    return true;
}
