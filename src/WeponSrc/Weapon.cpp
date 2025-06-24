#include "WeponInc/Weapon.h"
#include "GameObject/Character.h"  // Needed for Character*
#include "WorldInc/World.h"        // If not already included
#include <iostream>

Weapon::Weapon(WeaponType type): m_type(type)
{
}

std::vector<std::unique_ptr<Bullet>> Weapon::fire(World& world,
	const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner)
{
	std::vector<std::unique_ptr<Bullet>> bullets ;
	if (m_fireTimer > 0.f)
		return bullets;

	m_fireTimer = m_fireCooldown;
	m_shootingRange = 100.f; // Set a default shooting range, can be overridden by derived classes
	std::cout << typeid(*owner).name() << " " << static_cast<int>(m_type) << std::endl;
	if (m_type == WeaponType::SHOTGUN)
	{
		// Shotgun logic can be implemented here, e.g., firing multiple bullets in a spread pattern

		sf::Vector2f spreadDirection = direction + sf::Vector2f(std::cos(-20.f), std::sin(-20.f));
		bullets.push_back(std::make_unique<Bullet>(world, position, spreadDirection, owner));

		spreadDirection = direction;
		bullets.push_back(std::make_unique<Bullet>(world, position, spreadDirection, owner));

		spreadDirection = direction + sf::Vector2f(std::cos(20.f), std::sin(20.f));
		bullets.push_back(std::make_unique<Bullet>(world, position, spreadDirection, owner));


		//for (int i = 0; i < 3; ++i) // Example: fire 5 bullets
		//{
		//	float angleOffset = (i - 2) * 20.f; // Adjust the spread angle as needed
		//	sf::Vector2f spreadDirection = direction + sf::Vector2f(std::cos(angleOffset), std::sin(angleOffset));
		//	bullets.push_back(std::make_unique<Bullet>(world, position, spreadDirection, owner));
		//}
	}
	else {
		bullets.push_back(std::make_unique<Bullet>(world, position, direction, owner));
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

//int Weapon::getPrice(WeaponType type)
//{
//	switch (type) {
//	case WeaponType::BasicGun: return 0;
//	case WeaponType::Shotgun:  return 200;
//	case WeaponType::Sniper:   return 300;
//	case WeaponType::Laser:    return 500;
//	}
//	return 0;
//}
