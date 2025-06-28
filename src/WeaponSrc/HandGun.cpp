#include "WeaponInc/HandGun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

HandGun::HandGun() : Weapon(Constants::WeaponType::HandGun, 200.f, 5.f, 30.f)
{
}