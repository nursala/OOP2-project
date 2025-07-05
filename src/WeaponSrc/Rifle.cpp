#include "WeaponInc/Rifle.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

//-------------------------------------
// Rifle Constructor : initializes the weapon with specific parameters
//-------------------------------------
Rifle::Rifle() : Weapon(Constants::WeaponType::Rifle, 250.f, 13.f, 45.f)
{
	m_fireCooldown = 0.5f;
}
