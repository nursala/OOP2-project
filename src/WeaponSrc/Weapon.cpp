#include "WeaponInc/Weapon.h"
#include "GameObject/Character.h"  // Needed for Character*
#include "WorldInc/World.h"        // If not already included
#include <iostream>

Weapon::Weapon(WeaponType type, float shootingRange, float damage, float angle): m_type(type), m_shootingRange(shootingRange), m_damage(damage)
{
	m_weaponLight = std::make_unique<WeaponLight>(shootingRange, angle); // Correct type for m_weaponLight
	m_weaponLight->setIntensity(1.f); // Set default intensity for the weapon light
	m_weaponLight->setColor(sf::Color::Red); // Set default color for the weapon light
}

std::vector<std::unique_ptr<Bullet>> Weapon::fire(World& world,	const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner)
{
	std::vector<std::unique_ptr<Bullet>> bullets ;
	if (m_fireTimer > 0.f)
		return bullets;

	m_fireTimer = m_fireCooldown;
	bullets.push_back(std::make_unique<Bullet>(world, position, direction, owner, m_damage, m_weaponLight->getRange()));
	return bullets;
}

void Weapon::update(sf::Vector2f playerPos, float angle, float dt)
{
	m_fireTimer -= dt;
	if (m_weaponLight)
	{
		m_weaponLight->setPosition(playerPos - sf::Vector2f(20.f, 20.f));
		m_weaponLight->update(playerPos, angle / 30.f);
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

//void Weapon::setLight(std::shared_ptr<WeaponLight>& weaponLight)
//{
//	m_weaponLight = weaponLight;
//	m_weaponLight->setRange(m_shootingRange);
//}


float Weapon::getShootingRange() const
{
	return m_weaponLight->getRange();
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