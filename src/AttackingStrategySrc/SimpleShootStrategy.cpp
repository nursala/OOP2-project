#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"
#include "GameObject/Entity.h"
#include "WorldInc/World.h"
#include <iostream>

bool SimpleShootStrategy::attack(Character& self, float) {
    auto* weapon = self.getWeapon();
    if (!weapon)
        return false;

    Character* targetC = self.getTarget().get();
    if (!targetC)
        return false;

    sf::Vector2f target = targetC->getPosition();
    sf::Vector2f direction = target - self.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.f)
        return false;

    direction /= length;
    float muzzleOffset = 50.f;
    sf::Vector2f bulletPos = self.getPosition() + direction * muzzleOffset;

    self.getWorld().addBullets(weapon->fire(self.getWorld(), bulletPos, direction, self.shared_from_this()));

    return true;
    ////  Play weapon sound
    //if (dynamic_cast<HandGun*>(weapon))
    //    SoundManger::instance().play(Constants::SoundID::PISTOLSOUND);
    //else if (dynamic_cast<Shotgun*>(weapon))
    //    SoundManger::instance().play(Constants::SoundID::SHOTGUNSOUND);
    //else if (dynamic_cast<Sniper*>(weapon))
    //    SoundManger::instance().play(Constants::SoundID::SNIPERSOUND);
    //else
    //    SoundManger::instance().play(Constants::SoundID::RIFLESOUND);
}


