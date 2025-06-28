#include "GameSessionData.h"

GameSessionData& GameSessionData::instance() {
    static GameSessionData instance;
    return instance;
}


GameSessionData::GameSessionData()
    : money(200), selectedWeapon(Constants::WeaponType::HandGun) {
    ownedWeapons.insert(Constants::WeaponType::HandGun);
}

int& GameSessionData::getMoney()
{
    return money;
}

bool GameSessionData::hasWeapon(Constants::WeaponType weapon) const {
    return ownedWeapons.find(weapon) != ownedWeapons.end();
}

void GameSessionData::addWeapon(Constants::WeaponType weapon) {
    ownedWeapons.insert(weapon);
}

// GameSessionData.h
void GameSessionData::setSelectedWeapon(Constants::WeaponType weapon) {
    selectedWeapon = weapon;
    shouldUpdateWeapon = true;
}

Constants::WeaponType GameSessionData::getSelectedWeapon() const {
    return selectedWeapon;
}

void GameSessionData::setShouldUpdateWeapon(bool value) {
    shouldUpdateWeapon = value;
}

bool GameSessionData::getShouldUpdateWeapon() const {
    return shouldUpdateWeapon;
}
