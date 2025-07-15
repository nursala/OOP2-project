#include "WeaponInc/HandGun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

//-------------------------------------
// HandGun Constructor : initializes the weapon with specific parameters
//-------------------------------------
HandGun::HandGun() : Weapon(Constants::WeaponType::HandGun, 200.f, 10.f, 10.f)
{
	m_fireCooldown = 0.7f; // Set the cooldown for firing
}