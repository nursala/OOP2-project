#pragma once
#include "ResourseInc/BaseResourceManager.h"
#include <SFML/Graphics.hpp>
// TextureManager.h
enum class TextureID {
	Kill = 0,
	Player,
	Enemy,
	HEALTH,
	ARMOR,
	AMMO,
	DAMAGEDOWN,
	ENEMYSPEEDDOWN,
	SPEEDUP,
	SPY,

};

const std::unordered_map<TextureID, std::string> TextureFileMap = {
	{TextureID::Player, "heavy_player_face.png"},
	{TextureID::Enemy, "heavy_player_face.png"},
	{TextureID::HEALTH , "Health.png"},
	{TextureID::ARMOR, "shield.png"},
	{TextureID::AMMO, "ammo.png"},
	{TextureID::DAMAGEDOWN, "DamageDownGift.png"},
	{TextureID::ENEMYSPEEDDOWN, "EnemySpeedDownGift.png"},
	{TextureID::SPEEDUP, "SpeedUpGift.png"},
	{ TextureID::SPY, "spy.png" },
	{ TextureID::Kill, "kill.png" }}; 

class TextureManager : public BaseResourceManager<sf::Texture, TextureID> {
public:
	static TextureManager& instance();

private:
	TextureManager();
};