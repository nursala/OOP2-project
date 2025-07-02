#pragma once
#include <set>
#include "WeaponInc/Weapon.h"

class GameSessionData {
public:
    static GameSessionData& instance();

    void setSelectedWeapon(Constants::WeaponType weapon);
    Constants::WeaponType getSelectedWeapon() const;

    void setShouldUpdateWeapon(bool value);
    bool getShouldUpdateWeapon() const;

    void setEnemies(int enemies);
	void setHealth(int health);
    void setMoney(int money);
    int getEnemies() const;

    int getMoney() const;

    Constants::LevelID& getLevelID();

    int getHealth() const ;

    bool hasWeapon(Constants::WeaponType weapon) const;
    void addWeapon(Constants::WeaponType weapon);
private:
    GameSessionData();
    GameSessionData(const GameSessionData&) = delete;
    GameSessionData& operator=(const GameSessionData&) = delete;

    int m_money;
	int m_health;
    std::set<Constants::WeaponType> ownedWeapons;
    Constants::WeaponType selectedWeapon;
    bool shouldUpdateWeapon = false;
	int m_enemies;
	Constants::LevelID m_levelID;
};
