#include "WeaponInc/Shotgun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Shotgun::Shotgun() : Weapon(WeaponType::Shotgun)
{
	m_shootingRange = 100.f;
	m_damage = 7.f;
}
