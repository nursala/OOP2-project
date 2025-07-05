#include "WeaponInc/Sniper.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

//-------------------------------------
// Sniper Constructor : initializes the weapon with specific parameters
//-------------------------------------
Sniper::Sniper() : Weapon(Constants::WeaponType::Sniper, 300.f, 30.f, 15.f)
{
	m_fireCooldown = 1.0f; // Set the cooldown for firing
}