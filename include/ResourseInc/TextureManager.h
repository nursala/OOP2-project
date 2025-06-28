#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Graphics.hpp>

const std::unordered_map<Constants::TextureID, std::string> TextureFileMap = {
	{Constants::TextureID::Player, "Player_move.png"},
	{Constants::TextureID::Enemy, "Player_move.png"},
	{Constants::TextureID::HEALTH , "Health.png"},
	{Constants::TextureID::ARMOR, "shield.png"},
	{Constants::TextureID::BULLET, "game_bullet.png"},
	{Constants::TextureID::ENEMYSPEEDDOWN, "EnemySpeedDownGift.png"},
	{Constants::TextureID::SPEEDUP, "SpeedUpGift.png"},
	{ Constants::TextureID::SPY, "spy.png" },
	{ Constants::TextureID::MARKET, "market.JPG" },
	{ Constants::TextureID::HELP, "help.jpg" },
	{ Constants::TextureID::EASYMAP, "easy_map.png" },
	{ Constants::TextureID::MEDIUMMAP, "medium_map.png" },
	{ Constants::TextureID::HARDMAP, "hard_map.png" },
	{ Constants::TextureID::BUTTON, "button.png" },
	{ Constants::TextureID::SOUNDON, "soundon.png" },
	{ Constants::TextureID::SOUNDOFF, "soundoff.png" },
	{ Constants::TextureID::GOTOHOME, "home.png" },
	{ Constants::TextureID::PAUSE, "pause.png" },
	{ Constants::TextureID::HOMEPAGE, "homePage.png" },
	{ Constants::TextureID::BASICGUN, "basicGun.png" },
	{ Constants::TextureID::SHOTGUN, "shotgun.png" },
	{ Constants::TextureID::SNIPER, "sniper.png" },
	{ Constants::TextureID::RIFLE, "rifle.png" },
	{ Constants::TextureID::COINS, "coins.png" },
	{ Constants::TextureID::VISIONUP, "vision_up.png" },
	{ Constants::TextureID::KILLS, "kills.png" },
	{ Constants::TextureID::COINS, "coins.png" },
	{ Constants::TextureID::LEVELS, "Levels.png" },
	{ Constants::TextureID::MARKET, "market.JPG" },
};

class TextureManager : public BaseResourceManager<sf::Texture, Constants::TextureID> {
public:
	static TextureManager& instance();

private:
	TextureManager();
};