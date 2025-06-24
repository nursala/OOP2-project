#pragma once
#include <set>
#include "Macros.h"
#include "WeaponInc/Weapon.h"

class GameSessionData {
public:
    static GameSessionData& instance();



    void setSelectedWeapon(WeaponType weapon);
    WeaponType getSelectedWeapon() const;

    void setShouldUpdateWeapon(bool value);
    bool getShouldUpdateWeapon() const;

    int& getMoney();
    bool hasWeapon(WeaponType weapon) const;
    void addWeapon(WeaponType weapon);
private:
    GameSessionData();
    GameSessionData(const GameSessionData&) = delete;
    GameSessionData& operator=(const GameSessionData&) = delete;

    int money;
    std::set<WeaponType> ownedWeapons;
    WeaponType selectedWeapon;
    bool shouldUpdateWeapon = false;
    
};
