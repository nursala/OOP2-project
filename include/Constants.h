#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <unordered_map>
#include "CommandInc/Command.h"

namespace Constants {

	// ----------------------------
	// Window Settings
	// ----------------------------
	inline constexpr unsigned int WINDOW_WIDTH = 1600;
	inline constexpr unsigned int WINDOW_HEIGHT = 900;
	inline constexpr unsigned int WINDOW_HEIGHT_FOR_SCROLL = WINDOW_WIDTH * 1.78125;
	inline constexpr unsigned int FRAME_RATE = 60;
	inline constexpr unsigned int MARGIN = 15;
	// ----------------------------
	// Player Settings
	// ----------------------------
	inline constexpr float PLAYER_RADIUS = 20.f;
	inline constexpr float PLAYER_SPEED = 3.0f;
	inline constexpr float PLAYER_MAX_HEALTH = 100.f;

	// ----------------------------
	// Enemy Settings
	// ----------------------------
	inline constexpr float ENEMY_RADIUS = 18.f;
	inline constexpr float ENEMY_SPEED = 2.5f;

	// ----------------------------
	// Bullet Settings
	// ----------------------------
	inline constexpr float BULLET_SPEED = 8.0f;
	inline constexpr float BULLET_RADIUS = 5.f;
	inline constexpr float BULLET_LIFETIME = 2.f; // seconds

	// ----------------------------
	// sfml
	// ----------------------------
	const sf::Color HOVERD_COLOR = sf::Color(167, 167, 175);
	const sf::Color DEFAUL_BUTTON_COLOR = sf::Color::Green;
	const float CHAR_SIZE = 0.03 * WINDOW_WIDTH;
	// ----------------------------
	// Physics
	// ----------------------------
	inline constexpr float SCALE = 30.f; // pixels per meter
	inline const b2Vec2 GRAVITY(0.f, 0.f); // top-down game
	// ----------------------------
	//Screens
	// ----------------------------
	enum class ScreenID {
		Home,
		Settings,
		Game,
		GameOver,
		Market,
		Help,
		ChooseLevel,
	};
	// ----------------------------
	//Button IDs
	// ----------------------------
	enum class ButtonID {
		Play,
		Exit,
		Back,
		BasicGun,
		Shotgun,
		Sniper,
		Rifle,
		Easy,
		Medium,
		Hard,
		Help,
		ChooseLevel,
		BackToHome,
		BackToSettings,
		Market,
		SoundOn,
		SoundOff,
		GoToHome,
		Pause,
	};
	//------------------------------
	// ButtonInfo
	//------------------------------

	struct ButtonInfo {
		ButtonID id;
		std::string label;
		sf::Vector2f position;
		sf::Vector2f size;
		std::unique_ptr<Command> command;
	};
	// ----------------------------
	// Texture IDs
	// ----------------------------
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
		HELP,
		EASYMAP,
		MEDIUMMAP,
		HARDMAP,
		BUTTON,
		SOUNDON,
		SOUNDOFF,
		GOTOHOME,
		PAUSE,
		HOMEPAGE,
		BASICGUN,
		SHOTGUN,
		SNIPER,
		RIFLE,
		COINS,
	};
	// ----------------------------
	// Weapon IDs
	// ----------------------------
	enum class WeaponType {
		HandGun,
		Shotgun,
		Sniper,
		Rifle
	};
	//------------------------------
	// WeaponButtonInfo
	// -----------------------------
	struct WeaponButtonInfo
	{
		WeaponType type;
		ButtonID id;
		TextureID textureID;
		sf::Vector2f position;
		sf::Vector2f size;

	};

	// ----------------------------
	// Sound IDs
	// ----------------------------
	enum class SoundID {
		BackgroundMusic
	};
	// ----------------------------
	// Gift Types
	// ----------------------------
	enum class GiftType {
		ARMOR,
		HEALTH,
		ENEMYSPEEDDOWN,
		SPEEDUP,
		SPY,
		SIZE
	};

	// ----------------------------
	// Level IDs
	// ----------------------------
	enum class LevelID {
		EasyMap,
		MediumMap,
		HardMap
	};
	

	// ----------------------------  
	// Weapon Price  
	// ----------------------------  
	extern std::unordered_map<WeaponType, int> WeaponPrice;
}
