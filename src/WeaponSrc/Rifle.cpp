#include "WeaponInc/Rifle.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Rifle::Rifle() : Weapon(Constants::WeaponType::Rifle, 250.f, 13.f, 45.f)
{
	m_fireCooldown = 0.4f;
}
