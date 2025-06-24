#include "WeaponInc/Rifle.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Rifle::Rifle() : Weapon(WeaponType::Rifle)
{
	m_shootingRange = 100.f;
	m_damage = 10.f;
}
