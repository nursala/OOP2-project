#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "Bars/HealthBar.h"
#include "Bars/ArmorBar.h"
#include <WeaponInc/Weapon.h>
#include "VisionLight.h"

class World;
class Player : public Character 
{
public:
	Player(World& , b2Vec2& position);
	virtual ~Player() override = default;
     
   void update(float deltaTime);
   void takeDamage(int ) override;
   void addHealth();
   void addArmor();
   void addSpeed();
   void increaseVisionTemporarily(float extraRange, float duration);
   void rotateTowardMouse(sf::RenderWindow& ) ;
   bool isAlive() const { return m_alive; }  // or use m_alive if you prefer
   void render(RenderLayers& layers) override;
   static std::unique_ptr<Weapon> selectWeapon(Constants::WeaponType type);

private:
	bool m_alive = true; 
	bool m_visionBoostActive = false;
	float m_visionBoostTimer = 0.f;
	float m_originalVisionRange = 0.f;
	virtual Character* getClosestTarget()override;

	std::unique_ptr<ArmorBar> m_armorBar;
	float m_armor = 50.f;
};
