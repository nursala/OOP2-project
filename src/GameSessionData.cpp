#include "GameSessionData.h"
#include "iostream"
GameSessionData& GameSessionData::instance() {
    static GameSessionData instance;
    return instance;
}

GameSessionData::GameSessionData()
    : m_money(1000),m_health(100),selectedWeapon(Constants::WeaponType::HandGun) {
    ownedWeapons.insert(Constants::WeaponType::HandGun);
}

int& GameSessionData::getMoney()
{
    return m_money;
}

bool GameSessionData::hasWeapon(Constants::WeaponType weapon) const {
    return ownedWeapons.find(weapon) != ownedWeapons.end();
}

void GameSessionData::addWeapon(Constants::WeaponType weapon) {
    ownedWeapons.insert(weapon);
}

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

int& GameSessionData::getEnemies()
{
    return m_enemies;
}

Constants::LevelID& GameSessionData::getLevelID(){
	return m_levelID;
}

int& GameSessionData::getHealth () {
	return m_health;
}