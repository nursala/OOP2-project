#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/WalkingState.h"
#include <iostream>
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
	bool registered = [] {
		Factory::instance().registerType<Player, World&, b2Vec2&>(Constants::EntityType::Player);
		return true;
		}();
}

Player::Player(World& world, b2Vec2& position)
	: Character(world, position)
{
	m_animation = std::make_unique<Animation>(
		TextureManager::instance().get(Constants::TextureID::RIFLEMOVE),
		sf::Vector2u(3, 7), // 4 frames in the animation
		0.35f // frame time
	);


	m_sprite.setTexture(*TextureManager::instance().get(Constants::TextureID::RIFLEMOVE));
	m_sprite.setTextureRect(m_animation->getUvRect());

	m_state = std::make_unique<WalkingState>();
	m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
	m_attackStrategy = std::make_unique<SimpleShootStrategy>();

	// Use helper to create weapon
	m_weapon = std::make_unique<Rifle>();

	m_armorBar = std::make_unique<ArmorBar>(50.f, 5.f, 50);
	m_speed = 10.f;
	m_weapon->getWeaponLight()->setColor(sf::Color::Green);

	init(b2_dynamicBody, 1.5f);
}

void Player::update(float deltaTime) {
	Character::update(deltaTime);

	sf::Vector2f armorBarPos = { getPosition().x , getPosition().y + 20 };
	m_armorBar->setPosition(armorBarPos);
	m_armorBar->setValue(m_armor);

	if (m_visionBoostActive) {
		m_visionBoostTimer -= deltaTime;
		if (m_visionBoostTimer <= 0.f && m_visionLight) {
			m_visionLight->setRange(m_originalVisionRange);
			m_visionBoostActive = false;
		}
	}

	if (m_health < 20)
	{
		SoundManger::instance().play(Constants::SoundID::HEARTBEAT);
		SoundManger::instance().setVolume(Constants::SoundID::HEARTBEAT, 100.f);
	}
}

void Player::takeDamage(int damage)
{
	if (m_armor > 0) {
		float armorDamage = std::min(m_armor, static_cast<float>(damage));
		m_armor -= armorDamage;
		damage -= static_cast<int>(armorDamage);
	}
	if (damage > 0) {
		m_health -= damage;
		GameSessionData::instance().getHealth() -= damage; // Update player health in session data
		if (m_health < 0.f) m_health = 0.f;
	}
	if (m_health <= 0.f) {
		setDestroyed(true);   // Mark the player as destroyed
		m_alive = false;      // Optional: track status
		SoundManger::instance().play(Constants::SoundID::PLAYERDEATH);
	}
	//  Update the health bar (use Character's member)
	m_healthBar->setValue(m_health);
	m_armorBar->setValue(m_armor);
}

void Player::addHealth()
{
	m_health += 30; // Increase health by 20
	if (m_health > 100) m_health = 100; // Cap health at 100
	m_healthBar->setValue(m_health);
}

void Player::addArmor()
{
	m_armor += 30; // Increase armor by 10
	if (m_armor > 50) m_armor = 50; // Cap armor at 50
	m_armorBar->setValue(m_armor);
}

void Player::addSpeed()
{
	m_speed += 0.5f; // Increase speed by 0.5
	if (m_speed > 16.f) m_speed = 16.f; // Cap speed at 5
}

void Player::increaseVisionTemporarily(float extraRange, float duration)
{
	if (!m_visionBoostActive && m_visionLight) {
		m_originalVisionRange = m_visionLight->getRange();
		m_visionLight->setRange(m_originalVisionRange + extraRange);
		m_visionBoostTimer = duration;
		m_visionBoostActive = true;
	}
}

void Player::rotateTowardMouse(sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	sf::Vector2f direction = worldPos - getPosition(); // getPosition() returns player center
	float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
	setRotation(angle); // Implement this in your Character or Sprite wrapper
}
std::unique_ptr<Weapon> Player::selectWeapon(Constants::WeaponType type)
{
	switch (type) {
	case Constants::WeaponType::HandGun: return std::make_unique<HandGun>();
	case Constants::WeaponType::Shotgun: return std::make_unique<Shotgun>();
	case Constants::WeaponType::Sniper:  return std::make_unique<Sniper>();
	case Constants::WeaponType::Rifle:   return std::make_unique<Rifle>();
	default: return std::make_unique<HandGun>();
	}
}
void Player::render(RenderLayers& layers)
{
	Character::render(layers);
	m_armorBar->draw(layers);
}

Character* Player::getClosestTarget()
{
	for (auto* fixture : m_hitFixtures) {
		b2Body* body = fixture->GetBody();
		auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);

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

	if (!closestCharacter)
	{
		setTarget(nullptr); // Clear target if no closest character found
		return nullptr;

	}

	setTarget(closestCharacter->shared_from_this()); // Update target reference
	return closestCharacter;
}
