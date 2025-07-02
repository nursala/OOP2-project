#include "Constants.h"
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Rifle.h"
#include "WeaponInc/Shotgun.h"
#include "WeaponInc/Sniper.h"
#include "ResourseInc/TextureManager.h"

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

	std::unordered_map<GiftType, TextureID> GiftTextures = {
		{ GiftType::ARMOR, TextureID::ARMOR },
		{ GiftType::HEALTH, TextureID::HEALTH },
		{ GiftType::ENEMYSPEEDDOWN, TextureID::ENEMYSPEEDDOWN },
		{ GiftType::SPEEDUP, TextureID::SPEEDUP },
		{ GiftType::SPY, TextureID::SPY },
		{ GiftType::VISIONUP, TextureID::VISIONUP }
	};

    std::unordered_map<WeaponType, WeaponData> WeaponDataMap = {
        {
            WeaponType::HandGun,
            {
                [] { return std::make_unique<HandGun>(); },
                AnimationInfo(TextureID::HANDGUNMOVE, {7, 3}, 0.1f),
                AnimationInfo(TextureID::HANDGUNSHOOT, {1, 9}, 0.1f),
				SoundID::PISTOLSOUND
            }
        },
        {
            WeaponType::Rifle,
            {
                [] { return std::make_unique<Rifle>(); },
                AnimationInfo(TextureID::RIFLEMOVE, {3, 7}, 0.1f),
                AnimationInfo(TextureID::RIFLESHOOT, {1, 9}, 0.1f),
				SoundID::RIFLESOUND
            }
        },
        {
            WeaponType::Shotgun,
            {
                [] { return std::make_unique<Shotgun>(); },
                AnimationInfo(TextureID::SHOTGUNMOVE, {3, 7}, 0.1f),
                AnimationInfo(TextureID::SHOTGUNSHOOT, {1, 9}, 0.1f),
				SoundID::SHOTGUNSOUND
            }
        },
        {
            WeaponType::Sniper,
            {
                [] { return std::make_unique<Sniper>(); },
                AnimationInfo(TextureID::RIFLEMOVE, {3, 7}, 0.1f),
                AnimationInfo(TextureID::RIFLESHOOT, {1, 9}, 0.1f),
				SoundID::SNIPERSOUND
            }
        }
    };
}