#include "WeponInc/Weapon.h"

std::unique_ptr<Bullet> Weapon::fire(World& world,
	const sf::Vector2f& position, const sf::Vector2f& direction)
{
	if (m_fireTimer > 0.f)
		return nullptr; 
	m_fireTimer = m_fireCooldown;
	auto bullet = std::make_unique<Bullet>(world, position, direction);
	return bullet;
	m_shootingRange = 100.f; // Set a default shooting range, can be overridden by derived classes
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
	/*if (m_weaponLight)
		window.draw(*m_weaponLight);*/
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
