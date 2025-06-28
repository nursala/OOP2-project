#include "WeaponInc/Sniper.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Sniper::Sniper() : Weapon(Constants::WeaponType::Sniper)
{
	m_shootingRange = 100.f;
	m_damage = 10.f;
}