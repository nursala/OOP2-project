#include "GameSessionData.h"
#include "iostream"
GameSessionData& GameSessionData::instance() {
    static GameSessionData instance;
    return instance;
}

GameSessionData::GameSessionData()
    : m_money(100),m_health(100),selectedWeapon(Constants::WeaponType::HandGun) {
    ownedWeapons.insert(Constants::WeaponType::HandGun);
}

void GameSessionData::setMoney(int money) {
	m_money = money;
}
int GameSessionData::getMoney()const
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

void GameSessionData::setEnemies(int enemies)
{
	m_enemies = enemies;
}

int GameSessionData::getEnemies() const
{
    return m_enemies;
}


Constants::LevelID& GameSessionData::getLevelID(){
	return m_levelID;
}

void GameSessionData::setHealth(int health) {
	m_health = health;
}

int GameSessionData::getHealth () const{
	return m_health;
}