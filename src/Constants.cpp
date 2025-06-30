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
}