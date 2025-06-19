#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include <WeponInc/Weapon.h>

class World;
class Player : public Character<Player> {
public:
    Player(World& world);

    void setLight(std::shared_ptr<VisionLight>& visionLight);
    void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
    void setFacingRight(bool right);
    void setHealthBar(HealthBar* healthBar); // Add this
    void takeDamage(int damage);
    
private:
    bool m_visable = true;
    float m_health = 100.f;
    float m_armor = 50.f;
    HealthBar* m_healthBar = nullptr;
};
