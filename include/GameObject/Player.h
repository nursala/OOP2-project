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
   Player(World& );  
   void takeDamage(int ) override;
   void addHealth();
   void addArmor();
   void addSpeed();
    sf::Vector2f getTarget() const override;
    std::pair<bool, float> EnemyIsVisible() ;
	void rotateTowardMouse(sf::RenderWindow& ) ;
   
};
