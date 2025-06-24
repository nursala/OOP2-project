#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include "ArmorBar.h"
#include <WeaponInc/Weapon.h>
#include "VisionLight.h"

class World;
class Player : public Character {  
public:  
   Player(World& world);  
   void setLight(std::shared_ptr<VisionLight>& visionLight);  
   void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
   void setFacingRight(bool right);  
   //void setHealthBar(HealthBar* healthBar);  
   void takeDamage(int damage) override;
   void addHealth();
   void addArmor();
   void addSpeed();

    sf::Vector2f getTarget() const override;
    std::pair<bool, float> EnemyIsVisible() ;
private:
    std::shared_ptr<VisionLight> m_visionLight;
    bool m_visable = true;
};
