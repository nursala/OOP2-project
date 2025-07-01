#include "Constants.h"

namespace Constants {
    std::unordered_map<WeaponType, int> WeaponPrice = {
        { WeaponType::HandGun, 0 },
        { WeaponType::Rifle, 200 },
        { WeaponType::Shotgun, 300 },
        { WeaponType::Sniper, 400 }
    };

	std::unordered_map<LevelID, std::pair<std::string, sf::Color>> LevelNames = {
		{ LevelID::EasyMap, {"Easy", sf::Color::Green} },
		{ LevelID::MediumMap, {"Medium", sf::Color::Yellow} },
		{ LevelID::HardMap, {"Hard", sf::Color::Red} }
	};

     std::unordered_map<Constants::WeaponType,TextureID> SelectedWeapons = {
        {WeaponType::HandGun,TextureID::HANDGUNMOVE },
        {WeaponType::Shotgun,TextureID::SHOTGUNMOVE },
        {WeaponType::Rifle,TextureID::RIFLEMOVE }
        /*{WeaponType::Sniper,TextureID::SNIPERMOVE },*/
    };



	std::unordered_map<GiftType, TextureID> GiftTextures = {
		{ GiftType::ARMOR, TextureID::ARMOR },
		{ GiftType::HEALTH, TextureID::HEALTH },
		{ GiftType::ENEMYSPEEDDOWN, TextureID::ENEMYSPEEDDOWN },
		{ GiftType::SPEEDUP, TextureID::SPEEDUP },
		{ GiftType::SPY, TextureID::SPY },
		{ GiftType::VISIONUP, TextureID::VISIONUP }
	};
}