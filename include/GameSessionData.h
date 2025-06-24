#pragma once
#include <set>
#include "Macros.h"
#include "WeponInc/Weapon.h"

class GameSessionData {
public:
    static GameSessionData& instance();

    int money;
    std::set<WeaponType> ownedWeapons;
    WeaponType selectedWeapon;

    bool hasWeapon(WeaponType weapon) const;
    void addWeapon(WeaponType weapon);

private:
    GameSessionData();
    GameSessionData(const GameSessionData&) = delete;
    GameSessionData& operator=(const GameSessionData&) = delete;
};
