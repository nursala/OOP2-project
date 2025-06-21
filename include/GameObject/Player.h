#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include <WeponInc/Weapon.h>
#include "VisionLight.h"

class World;
class Player : public Character {
public:
    Player(World& world);

    void setLight(std::shared_ptr<VisionLight>& visionLight);
    void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
    void setFacingRight(bool right);
    sf::Vector2f getTarget() const override;
    void shoot(float dt);
private:
    std::shared_ptr<VisionLight> m_visionLight;
    bool m_visable = true;
};
