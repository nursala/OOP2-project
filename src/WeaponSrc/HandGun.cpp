#include "WeaponInc/HandGun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

HandGun::HandGun() : Weapon(WeaponType::HandGun)
{
	 m_shootingRange = 100.f; 
	 m_damage = 5.f;
}