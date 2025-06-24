#include "WeaponInc/Weapon.h"
#include "GameObject/Character.h"  // Needed for Character*
#include "WorldInc/World.h"        // If not already included
#include <iostream>

Weapon::Weapon(WeaponType type): m_type(type)
{
	m_weaponLight = std::make_unique<WeaponLight>(100, 30); // Correct type for m_weaponLight
	m_weaponLight->setIntensity(1.f); // Set default intensity for the weapon light
	m_weaponLight->setColor(sf::Color::Red); // Set default color for the weapon light
}

std::vector<std::unique_ptr<Bullet>> Weapon::fire(World& world,
	const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner)
{
	std::vector<std::unique_ptr<Bullet>> bullets ;
	if (m_fireTimer > 0.f)
		return bullets;

	m_fireTimer = m_fireCooldown;
	m_shootingRange = 100.f; // Set a default shooting range, can be overridden by derived classes
	//std::cout << typeid(*owner).name() << " " << static_cast<int>(m_type) << std::endl;
	if (m_type == WeaponType::Shotgun)
	{
		// Shotgun logic - fire one bullet straight and two bullets at angles
		// Straight bullet
		bullets.push_back(std::make_unique<Bullet>(world, position, direction, owner, m_damage));
		
		// Left bullet (20 degrees counterclockwise)
		float leftAngle = -20.f * 3.14159f / 180.f; // Convert to radians
		sf::Vector2f leftDir = sf::Vector2f(
			direction.x * std::cos(leftAngle) - direction.y * std::sin(leftAngle),
			direction.x * std::sin(leftAngle) + direction.y * std::cos(leftAngle)
		);
		bullets.push_back(std::make_unique<Bullet>(world, position, leftDir, owner, m_damage));
		
		// Right bullet (20 degrees clockwise)
		float rightAngle = 20.f * 3.14159f / 180.f; // Convert to radians
		sf::Vector2f rightDir = sf::Vector2f(
			direction.x * std::cos(rightAngle) - direction.y * std::sin(rightAngle),
			direction.x * std::sin(rightAngle) + direction.y * std::cos(rightAngle)
		);
		bullets.push_back(std::make_unique<Bullet>(world, position, rightDir, owner, m_damage));
	}
	else {
		bullets.push_back(std::make_unique<Bullet>(world, position, direction, owner, m_damage));
	}
	return bullets;
}

void Weapon::update(sf::Vector2f playerPos, float angle, float dt)
{
	m_fireTimer -= dt;
	if (m_weaponLight)
	{
		m_weaponLight->setPosition(playerPos);
		m_weaponLight->update(playerPos, angle);
	}
}

void Weapon::draw(sf::RenderWindow&)
{
	// You may restore this if you want to visualize weapon light
	// if (m_weaponLight)
	//     window.draw(*m_weaponLight);
}
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
	return m_shootingRange;
}

WeaponLight* Weapon::getWeaponLight()
{
	return m_weaponLight.get();
}

int Weapon::getPrice(WeaponType type)
{
	switch (type) {
	case WeaponType::HandGun: return 0;
	case WeaponType::Shotgun:  return 200;
	case WeaponType::Sniper:   return 300;
	case WeaponType::Rifle:    return 500;
	}
	return 0;
}


float Weapon::getDamage() const
{
	return m_damage;
}

void Weapon::setDamage(float damage)
{
	m_damage = damage;
}