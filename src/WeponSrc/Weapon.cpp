#include "WeponInc/Weapon.h"
#include "GameObject/Character.h"  // Needed for Character*
#include "WorldInc/World.h"        // If not already included

std::unique_ptr<Bullet> Weapon::fire(World& world,
	const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner)
{
	if (m_fireTimer > 0.f)
		return nullptr;

	m_fireTimer = m_fireCooldown;
	m_shootingRange = 100.f; // Set a default shooting range, can be overridden by derived classes

	return std::make_unique<Bullet>(world, position, direction, owner);
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

void Weapon::draw(sf::RenderWindow& window)
{
	// You may restore this if you want to visualize weapon light
	// if (m_weaponLight)
	//     window.draw(*m_weaponLight);
}

void Weapon::setLight(std::shared_ptr<WeaponLight>& weaponLight)
{
	m_weaponLight = weaponLight;
}

float Weapon::getShootingRange() const
{
	return m_shootingRange;
}

WeaponLight* Weapon::getWeaponLight()
{
	return m_weaponLight.get();
}
