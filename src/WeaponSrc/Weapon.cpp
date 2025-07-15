#include "WeaponInc/Weapon.h"
#include "GameObject/Character.h"  // Needed for Character*
#include "WorldInc/World.h"        // If not already included
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Shotgun.h"
#include "WeaponInc/Sniper.h"
#include "ResourseInc/SoundManager.h"
#include "Factory.h"
#include <iostream>
#include <numbers>

//-------------------------------------
// Weapon Constructor : initializes the weapon with specific parameters
//-------------------------------------
Weapon::Weapon(Constants::WeaponType type, float shootingRange, 
			float damage, float angle): m_type(type), m_shootingRange(shootingRange), m_damage(damage)
{
	m_weaponLight = std::make_unique<WeaponLight>(shootingRange, angle); // Correct type for m_weaponLight
	m_weaponLight->setIntensity(1.f); // Set default intensity for the weapon light
	m_weaponLight->setColor(sf::Color::Red); // Set default color for the weapon light
}

//-------------------------------------
// Creates and returns bullets fired from the weapon
//-------------------------------------
std::vector<std::unique_ptr<Bullet>> Weapon::fire(World& world,	const b2Vec2& position,
					const sf::Vector2f& direction, std::shared_ptr<Character> owner)
{
	std::vector<std::unique_ptr<Bullet>> bullets;
	if (m_fireTimer > 0.f)
		return bullets;

	float radians = m_weaponLight->getRotation() * std::numbers::pi / 180.f;
	sf::Vector2f weaponDirection = { std::cos(radians), std::sin(radians) };

	// Compute angle between weapon direction and fire direction
	float dot = weaponDirection.x * direction.x + weaponDirection.y * direction.y;
	dot = std::clamp(dot, -1.f, 1.f);
	float angleDeg = std::acos(dot) * 180.f / std::numbers::pi;

	// Use weapon light's beam angle as shooting cone
	float maxAngle = m_weaponLight->getBeamAngle();
	if (angleDeg > maxAngle)
		return bullets;

	m_fireTimer = m_fireCooldown;

	auto bullet = Factory::instance().createAs<Bullet>(
		Constants::EntityType::Bullet,
		world,
		position,
		direction,
		owner,
		m_damage,
		m_weaponLight->getRange()
	);

	bullets.push_back(std::move(bullet));
	return bullets;
}

//-------------------------------------
// Set the shooting range of the weapon
//-------------------------------------
void Weapon::update(sf::Vector2f playerPos, float angle, float dt)
{
	m_fireTimer -= dt;
	if (m_weaponLight)
	{
		m_weaponLight->setPosition(playerPos - sf::Vector2f(20.f, 20.f));
		m_weaponLight->update(playerPos, angle / 30.f);
	}
}

//-------------------------------------
// Set the shooting range of the weapon
//-------------------------------------
void Weapon::draw(RenderLayers& renderLayers)
{
	if (m_weaponLight)
	{
		renderLayers.drawLight(*m_weaponLight);
		renderLayers.drawForeground(*m_weaponLight);
	}
}

float Weapon::getShootingRange() const
{
	return m_weaponLight->getRange() - 10.f;
}

WeaponLight* Weapon::getWeaponLight()
{
	return m_weaponLight.get();
}

float Weapon::getFireTimer() const
{
	return m_fireTimer;
}