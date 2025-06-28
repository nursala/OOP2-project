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
   void update(float deltaTime);
   void takeDamage(int ) override;
   void addHealth();
   void addArmor();
   void addSpeed();
   void increaseVisionTemporarily(float extraRange, float duration);
   sf::Vector2f getTarget() const override;
   std::pair<bool, float> EnemyIsVisible() ;
   void rotateTowardMouse(sf::RenderWindow& ) ;
   bool isAlive() const { return m_alive; }  // or use m_alive if you prefer

private:
	bool m_alive = true; // Track if the player is alive
	bool m_visionBoostActive = false;
	float m_visionBoostTimer = 0.f;
	float m_originalVisionRange = 0.f;
	virtual Character* getClosestTarget()override;
};
