#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <unordered_map>
#include "CommandInc/Command.h"
#include <optional>
#include <memory>
#include <string>
#include <functional>

class Weapon;
namespace Constants {

	// ----------------------------
	// Window Settings
	// ----------------------------
	inline constexpr unsigned int WINDOW_WIDTH = 1280;
	inline constexpr unsigned int WINDOW_HEIGHT = 720;
	inline constexpr float WINDOW_HEIGHT_FOR_SCROLL = WINDOW_WIDTH * 1.78125;
	inline constexpr unsigned int FRAME_RATE = 60;
	inline constexpr unsigned int MARGIN = 15;
	inline constexpr unsigned int NUM_OF_ITEMS_IN_STATUS_BAR = 3;
	inline constexpr float TILE_IN_STATUS_BAR = WINDOW_WIDTH * 0.05;
	inline constexpr float BUTTON_IN_STATUS_BAR = WINDOW_WIDTH * 0.03;
	// ----------------------------
	// Player Settings
	// ----------------------------
	inline constexpr float PLAYER_RADIUS = 20.f;
	inline constexpr float PLAYER_SPEED = 3.0f;
	inline constexpr int PLAYER_MAX_HEALTH = 100;

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
	const sf::Color DEFAUL_BUTTON_COLOR = sf::Color::White;
	const float CHAR_SIZE = 0.03 * WINDOW_WIDTH;
	// ----------------------------
	// Physics
	// ----------------------------
	inline constexpr float SCALE = 30.f; // pixels per meter
	inline const b2Vec2 GRAVITY(0.f, 0.f); // top-down game

	//-----------------------------
	// Entity Types
	//-----------------------------
	enum class EntityType
	{
		Player,
		Enemy,
		Bullet,
		Gift,
		Spy
	};
	// ----------------------------
	//Screens
	// ----------------------------
	enum class ScreenID {
		Home,
		Settings,
		Game,
		GameOver,
		GameWin,
		Market,
		Help,
		ChooseLevel,
		Pause,
		SplashScreen,
		LoadGame
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
		Pause,
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
		VISIONUP,
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
		CHOOSEMAP,
		COINSMARKET,
		KILLS,
		LEVELS,
		HANDGUNSHOOT,
		SHOTGUNSHOOT,
		SNIPERSHOOT,
		RIFLESHOOT,
		HANDGUNMOVE,
		SHOTGUNMOVE,
		RIFLEMOVE,
		PAUSESCREEN,
		GAMEOVER,
		GAMEWIN,
		LOADGAME,
	};
	// ----------------------------
	// Weapon IDs
	// ----------------------------
	enum class WeaponType {
		HandGun,
		Shotgun,
		Sniper,
		Rifle,
		Size 
	};

	// ----------------------------
	// Generic Button Structure
	// ----------------------------
	template <typename T = std::monostate>
	struct GenericButton {
		Constants::ButtonID id;
		std::string label;
		sf::Vector2f position;
		sf::Vector2f size;
		std::unique_ptr<Command> command;
		std::optional<TextureID> textureID;
		std::optional<T> type = std::nullopt;
		std::optional<sf::Color> color;
	};

	// ----------------------------
	// Sound IDs
	// ----------------------------
	enum class SoundID {
		SHOOT,
		BACKGROUNDMUSIC,
		MENUMUSIC,
		MATCHMAKINGMUSIC,
		GAMEOVERSOUND,
		GAMEWINSOUND,
		RIFLESOUND,
		SHOTGUNSOUND,
		PISTOLSOUND,
		SNIPERSOUND,
		BUTTOUNEVENT,
		HEARTBEAT,
		VISIONUPGRADE,
		SHIELDUPGRADE,
		HEALTHUPGRADE,
		SPEEDUPGRADE,
		SPEEDDOWN,
		SPY,
		GAMEBEGIN,
		ENEMYDEATH,
		PLAYERDEATH,
		COINS,
		FOOTSTEP,
		SCENARIO,
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
		VISIONUP,
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
	//------------------------------
	// Animation Info Structure
	//------------------------------
	struct AnimationInfo {
		TextureID textureID;
		sf::Vector2u frameSize;
		float speed;
	};

	// ----------------------------
	// Weapon Data Structure
	// ----------------------------
	struct WeaponData {
		std::function<std::unique_ptr<Weapon>()> weaponFactory;
		AnimationInfo moveAnim;
		AnimationInfo shootAnim;
		SoundID shootSound;
	};

	// ----------------------------
	// Level Names and Colors
	// ----------------------------
	extern std::unordered_map<LevelID, std::pair<std::string, sf::Color>> LevelNames;
	// ----------------------------  
	// Weapon Price  
	// ----------------------------  
	extern std::unordered_map<WeaponType, int> WeaponPrice;
	// ----------------------------
	// Gifts Textures
	// ----------------------------
	extern std::unordered_map<GiftType, TextureID> GiftTextures;
	// ----------------------------
	// Weapon Data Map
	// ----------------------------
	extern std::unordered_map<WeaponType, WeaponData> WeaponDataMap;
	//-----------------------------
	//Map Level And Textuer
	//-----------------------------
	extern std::unordered_map<LevelID, TextureID> LevelTexture;

}
