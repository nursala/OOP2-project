#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include <WeponInc/Weapon.h>

class World;
class Player : public Character {
public:
    Player(World& world);

    void setLight(std::shared_ptr<VisionLight>& visionLight);
    void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
    void setFacingRight(bool right);
    
private:
    bool m_visable = true;
};
