#include "Constants.h"

namespace Constants {
    std::unordered_map<WeaponType, int> WeaponPrice = {
        { WeaponType::HandGun, 0 },
        { WeaponType::Rifle, 200 },
        { WeaponType::Shotgun, 300 },
        { WeaponType::Sniper, 400 }
    };
}