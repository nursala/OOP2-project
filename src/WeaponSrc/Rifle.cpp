#include "WeaponInc/Rifle.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Rifle::Rifle() : Weapon(Constants::WeaponType::Rifle, 200.f, 10.f, 45.f)
{
}
