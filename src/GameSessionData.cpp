//#include "GameSessionData.h"
//
//GameSessionData& GameSessionData::instance() {
//    static GameSessionData instance;
//    return instance;
//}
//
//GameSessionData::GameSessionData()
//    : money(0), selectedWeapon(WeaponType::BasicGun) {
//    ownedWeapons.insert(WeaponType::BasicGun);
//}
//
//bool GameSessionData::hasWeapon(WeaponType weapon) const {
//    return ownedWeapons.find(weapon) != ownedWeapons.end();
//}
//
//void GameSessionData::addWeapon(WeaponType weapon) {
//    ownedWeapons.insert(weapon);
//}
