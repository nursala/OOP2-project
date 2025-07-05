#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "StatesInc/WalkingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "WorldInc/World.h"
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Shotgun.h"
#include <cmath>
#include <limits>

//=========================================================
// Factory registration
//=========================================================
namespace {
	bool registered = [] {
		Factory::instance().registerType<Enemy, World&, const b2Vec2&, const LoadMap&,
			const Player&, const Constants::WeaponType&>(
				Constants::EntityType::Enemy);
		return true;
		}();
}

//=========================================================
// Constructor
//=========================================================
Enemy::Enemy(World& world, const b2Vec2& position, const LoadMap& map,
	const Player& player, const Constants::WeaponType& type)
	: Character(world, position), m_playerRef(player)
{
	auto& weaponData = Constants::WeaponDataMap.at(type);

	m_animation = std::make_unique<Animation>(
		TextureManager::instance().get(weaponData.moveAnim.textureID),
		weaponData.moveAnim.frameSize,
		weaponData.moveAnim.speed
	);

	m_weapon = weaponData.weaponFactory();

	m_sprite.setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));
	m_sprite.setTextureRect(m_animation->getUvRect());

	m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, rand() % 10 + 1);
	m_state = std::make_unique<WalkingState>();
	m_attackStrategy = std::make_unique<SimpleShootStrategy>();

	m_speed = m_originalSpeed = 7.f;
	m_visable = false;

	init(b2_dynamicBody, 1.3f);
}

//=========================================================
// Get closest visible character (based on vision/light)
//=========================================================
Character* Enemy::getClosestTarget()
{
	if (auto currentTarget = getTarget()) {
		for (b2Fixture* fixture = currentTarget->getBody()->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
			if (m_hitFixtures.find(fixture) != m_hitFixtures.end())
				return currentTarget.get();
		}

		// Check if within light radius
		sf::Vector2f targetPos = currentTarget->getPosition();
		float distSq = std::pow(targetPos.x - getPosition().x, 2) +
			std::pow(targetPos.y - getPosition().y, 2);
		float radius = currentTarget->getWeapon()->getWeaponLight()->getRange();
		if (distSq <= radius * radius)
			return currentTarget.get();
	}

	if (m_hitFixtures.empty()) {
		setTarget(nullptr);
		return nullptr;
	}

	Character* closest = nullptr;
	float minDist = std::numeric_limits<float>::max();
	sf::Vector2f lightPos = m_weapon->getWeaponLight()->getPosition();

	for (auto* fixture : m_hitFixtures) {
		auto* character = reinterpret_cast<Character*>(fixture->GetBody()->GetUserData().pointer);
		if (!character) continue;

		if (auto* enemy = dynamic_cast<Enemy*>(character)) {
			if ((isSpy() && enemy->isSpy()) || (!isSpy() && !enemy->isSpy()))
				continue;
		}

		if (dynamic_cast<Player*>(character) && isSpy())
			continue;

		float dist = std::hypot(character->getPosition().x - lightPos.x,
								character->getPosition().y - lightPos.y);

		if (dist < minDist) {
			if (closest && dynamic_cast<Player*>(closest) && !isSpy()) {
				continue;
			}
			minDist = dist;
			closest = character;
		}
	}

	setTarget(closest ? closest->shared_from_this() : nullptr);
	return closest;
}

//=========================================================
// Apply damage to health
//=========================================================
void Enemy::takeDamage(const int damage)
{
	if (m_health > 0) {
		m_health = std::max(m_health - damage, 0.f);
		m_healthBar->setValue(m_health);
	}
}

//=========================================================
// Update function called every frame
//=========================================================
void Enemy::update(const float deltaTime)
{
	if (auto enemy = dynamic_cast<Enemy*>(getTarget().get()))
	{
		if (isSpy() && enemy->isSpy()) {
			getClosestTarget();
		}
		else if (!isSpy() && !enemy->isSpy()) {
			setTarget(nullptr);
		}
	}

	if (getTarget() || isSpy()) {
		setVisible(true);
		m_hideDelayTimer = 0.2f;
	}
	else if (m_hideDelayTimer > 0.f) {
		m_hideDelayTimer -= deltaTime;
		if (m_hideDelayTimer <= 0.f)
			setVisible(false);
	}

	Character::update(deltaTime);

	if (m_health <= 0.f) {
		setDestroyed(true);
		return;
	}

	if (m_isSpy) {
		m_spyTimer -= deltaTime;
		if (m_spyTimer <= 0.f)
			setSpy(false);
	}

	if (m_speedDownTimer > 0.f) {
		m_speedDownTimer -= deltaTime;
		if (m_speedDownTimer <= 0.f)
			m_speed = m_originalSpeed;
	}

	m_weapon->getWeaponLight()->setColor(m_isSpy ? sf::Color::Blue : sf::Color::Red);
}

//=========================================================
// Reduce enemy's movement speed
//=========================================================
void Enemy::speedDown()
{
	m_speed = std::max(m_speed - 0.2f, 4.f);
}

//=========================================================
// Start slow effect for given duration
//=========================================================
void Enemy::setSpeedDownTimer(const float seconds)
{
	speedDown();
	m_speedDownTimer = seconds;
}

//=========================================================
// Enable/disable spy mode
//=========================================================
void Enemy::setSpy(const bool value)
{
	m_isSpy = value;
	m_visable = value;
	setTarget(nullptr);
}

//=========================================================
// Check if enemy is in spy mode
//=========================================================
bool Enemy::isSpy() const
{
	return m_isSpy;
}

//=========================================================
// Set spy timer duration
//=========================================================
void Enemy::setSpyTimer(const float seconds)
{
	m_spyTimer = seconds;
}

//=========================================================
// Play footstep sound based on distance to player
//=========================================================
void Enemy::updateFootstepSound(const float distanceToPlayer, const float deltaTime)
{
	if (isSpy())
		return;

	const float footstepDistanceThreshold = 1050.f;
	const float maxInterval = 1.0f;
	const float minInterval = 0.25f;
	const float maxVolume = 110.f;
	const float minVolume = 60.f;

	float normalizedDist = std::clamp(distanceToPlayer / footstepDistanceThreshold, 0.f, 1.f);
	m_footstepInterval = minInterval + (maxInterval - minInterval) * normalizedDist;

	m_footstepTimer += deltaTime;
	if (m_footstepTimer >= m_footstepInterval) {
		if (distanceToPlayer <= footstepDistanceThreshold &&
			!SoundManager::instance().isPlaying(Constants::SoundID::FOOTSTEP)) {
			SoundManager::instance().play(Constants::SoundID::FOOTSTEP);
			float volume = maxVolume - (maxVolume - minVolume) * normalizedDist;
			SoundManager::instance().setVolume(Constants::SoundID::FOOTSTEP, volume);

			m_footstepTimer = 0.f;
		}
	}
}
