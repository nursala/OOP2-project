#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Graphics.hpp>
// TextureManager.h
enum class TextureID {
	Player,
	Enemy,
	ARMOR,
	HEALTH,
	ENEMYSPEEDDOWN,
	SPEEDUP,
	SPY,
	SIZE,
	BULLET,
	MARKET,
	HELP
};

const std::unordered_map<TextureID, std::string> TextureFileMap = {
	{TextureID::Player, "Player_move.png"},
	{TextureID::Enemy, "Player_move.png"},
	{TextureID::HEALTH , "Health.png"},
	{TextureID::ARMOR, "shield.png"},
	{TextureID::BULLET, "game_bullet.png"},
	{TextureID::ENEMYSPEEDDOWN, "EnemySpeedDownGift.png"},
	{TextureID::SPEEDUP, "SpeedUpGift.png"},
	{ TextureID::SPY, "spy.png" },
	{ TextureID::MARKET, "market.JPG" },
	{ TextureID::HELP, "help.jpg" },
};

class TextureManager : public BaseResourceManager<sf::Texture, TextureID> {
public:
	static TextureManager& instance();

private:
	TextureManager();
};