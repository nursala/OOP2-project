#include "GameSessionData.h"

GameSessionData& GameSessionData::instance() {
    static GameSessionData instance;
    return instance;
}


GameSessionData::GameSessionData()
    : money(200), selectedWeapon(WeaponType::HandGun) {
    ownedWeapons.insert(WeaponType::HandGun);
}

int& GameSessionData::getMoney()
{
    return money;
}

bool GameSessionData::hasWeapon(WeaponType weapon) const {
    return ownedWeapons.find(weapon) != ownedWeapons.end();
}

void GameSessionData::addWeapon(WeaponType weapon) {
    ownedWeapons.insert(weapon);
}

// GameSessionData.h
void GameSessionData::setSelectedWeapon(WeaponType weapon) {
    selectedWeapon = weapon;
    shouldUpdateWeapon = true;
}

WeaponType GameSessionData::getSelectedWeapon() const {
    return selectedWeapon;
}

void GameSessionData::setShouldUpdateWeapon(bool value) {
    shouldUpdateWeapon = value;
}

bool GameSessionData::getShouldUpdateWeapon() const {
    return shouldUpdateWeapon;
}
