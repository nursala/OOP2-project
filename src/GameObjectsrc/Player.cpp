// Player.cpp
// Author: [Your Name]
// ID: [Your ID]
// Login: [Your Login]
// Description: Implements the logic of the Player class including input handling, upgrades, damage logic, and target detection.

#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/WalkingState.h"
#include <unordered_map>
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Shotgun.h"
#include "WeaponInc/Sniper.h"
#include "WeaponInc/Rifle.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "WorldInc/World.h"
#include "ResourseInc/SoundManger.h"
#include "GameSessionData.h"

namespace {
	// Register the Player class with the factory
	bool registered = [] {
		Factory::instance().registerType<Player, World&, const b2Vec2&>(Constants::EntityType::Player);
		return true;
		}();
}

//---------------------------------------------
// Constructor: Initializes weapon, movement, attack strategy, animation, etc.
//---------------------------------------------
Player::Player(World& world, const b2Vec2& position)
	: Character(world, position)
{
	auto& weaponData = Constants::WeaponDataMap.at(GameSessionData::instance().getSelectedWeapon());

	m_animation = std::make_unique<Animation>(
		TextureManager::instance().get(weaponData.moveAnim.textureID),
		weaponData.moveAnim.frameSize,
		weaponData.moveAnim.speed);

	m_sprite.setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));
	m_sprite.setTextureRect(m_animation->getUvRect());

	m_weapon = weaponData.weaponFactory();
	m_weapon->getWeaponLight()->setColor(sf::Color::Green);

	m_state = std::make_unique<WalkingState>();
	m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
	m_attackStrategy = std::make_unique<SimpleShootStrategy>();

	m_armorBar = std::make_unique<ArmorBar>(50.f, 5.f, 50);
	m_speed = 9.f;

	init(b2_dynamicBody, 1.3f);
}

//---------------------------------------------
// Updates the player per frame: weapon swap, vision boost, animation, etc.
//---------------------------------------------
void Player::update(const float deltaTime)
{
	// Handle weapon change
	if (GameSessionData::instance().getShouldUpdateWeapon())
	{
		m_weapon = std::move(Constants::WeaponDataMap.at(GameSessionData::instance().getSelectedWeapon()).weaponFactory());
		m_weapon->getWeaponLight()->setColor(sf::Color::Green);

		auto& weaponData = Constants::WeaponDataMap.at(m_weapon->getType());
		m_animation->setAll(
			TextureManager::instance().get(weaponData.moveAnim.textureID),
			weaponData.moveAnim.frameSize,
			weaponData.moveAnim.speed
		);
		m_sprite.setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));

		GameSessionData::instance().setShouldUpdateWeapon(false);
	}

	// Call base class update (Character)
	Character::update(deltaTime);

	// Update armor bar position and value
	sf::Vector2f armorBarPos = { getPosition().x , getPosition().y + 20 };
	m_armorBar->setPosition(armorBarPos);
	m_armorBar->setValue(m_armor);

	// Handle temporary vision boost
	if (m_visionBoostActive) {
		m_visionBoostTimer -= deltaTime;
		if (m_visionBoostTimer <= 0.f && m_visionLight) {
			m_visionLight->setRange(m_originalVisionRange);
			m_visionBoostActive = false;
		}
	}
}

//---------------------------------------------
// Applies damage to player (armor first), then health
//---------------------------------------------
void Player::takeDamage(int damage)
{
	if (m_armor > 0) {
		float armorDamage = std::min(m_armor, static_cast<float>(damage));
		m_armor -= armorDamage;
		damage -= static_cast<int>(armorDamage);
	}
	if (damage > 0) {
		m_health -= damage;
		GameSessionData::instance().setHealth(GameSessionData::instance().getHealth() - damage);
		if (m_health < 0.f) m_health = 0.f;
	}

	if (m_health <= 0.f) {
		setDestroyed(true);
		m_alive = false;
		SoundManger::instance().play(Constants::SoundID::PLAYERDEATH);
	}

	m_healthBar->setValue(m_health);
	m_armorBar->setValue(m_armor);
}

//---------------------------------------------
// Heals player (up to max 100)
//---------------------------------------------
void Player::addHealth()
{
	m_health += 30.f;
	if (m_health > 100.f) m_health = 100.f;
	m_healthBar->setValue(m_health);
}

//---------------------------------------------
// Adds armor (up to max 50)
//---------------------------------------------
void Player::addArmor()
{
	m_armor += 30.f;
	if (m_armor > 50.f) m_armor = 50.f;
	m_armorBar->setValue(m_armor);
}

//---------------------------------------------
// Increases player speed (up to cap)
//---------------------------------------------
void Player::addSpeed()
{
	m_speed += 0.5f;
	if (m_speed > 16.f) m_speed = 16.f;
}

//---------------------------------------------
// Temporarily increases vision range
//---------------------------------------------
void Player::increaseVisionTemporarily(const float extraRange, const float duration)
{
	if (!m_visionBoostActive && m_visionLight) {
		m_originalVisionRange = m_visionLight->getRange();
		m_visionLight->setRange(m_originalVisionRange + extraRange);
		m_visionBoostTimer = duration;
		m_visionBoostActive = true;
	}
}

//---------------------------------------------
// Rotates the player sprite toward mouse pointer
//---------------------------------------------
void Player::rotateTowardMouse(sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	sf::Vector2f direction = worldPos - getPosition();

	float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
	setRotation(angle);
}

//---------------------------------------------
// Renders the player + armor bar
//---------------------------------------------
void Player::render(RenderLayers& layers)
{
	Character::render(layers);
	m_armorBar->draw(layers);
}

//---------------------------------------------
// Finds the closest visible target in cone
//---------------------------------------------
Character* Player::getClosestTarget()
{
	for (auto* fixture : m_hitFixtures) {
		b2Body* body = fixture->GetBody();
		auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);
		if (character)
			character->setVisible(true);
	}

	Character* closestCharacter = nullptr;
	float minDistSq = std::numeric_limits<float>::max();
	sf::Vector2f lightPos = m_weapon->getWeaponLight()->getPosition();

	for (auto* fixture : m_hitFixtures) {
		b2Body* body = fixture->GetBody();
		auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);

		if (!character || !character->isVisible()) continue;

		auto* enemy = dynamic_cast<Enemy*>(character);
		if (!enemy || enemy->isSpy()) continue;

		sf::Vector2f charPos = character->getPosition();
		float dx = charPos.x - lightPos.x;
		float dy = charPos.y - lightPos.y;
		float distSq = std::sqrt(dx * dx + dy * dy);

		if (distSq < minDistSq) {
			minDistSq = distSq;
			closestCharacter = character;
		}
	}

	if (!closestCharacter) {
		setTarget(nullptr);
		return nullptr;
	}

	setTarget(closestCharacter->shared_from_this());
	return closestCharacter;
}
