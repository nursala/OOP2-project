#include "WeponInc/Weapon.h"

std::unique_ptr<Bullet> Weapon::fire(World& world,
	const sf::Vector2f& position, const sf::Vector2f& direction)
{
	auto bullet = std::make_unique<Bullet>(world, position, direction);
	return bullet;
}

void Weapon::update(sf::Vector2f playerPos, float angle)
{
	if (m_weaponLight)
	{
		m_weaponLight->setPosition(playerPos);
		m_weaponLight->update(playerPos, angle);
	}
}

void Weapon::draw(sf::RenderWindow& window)
{
	if (m_weaponLight)
		window.draw(*m_weaponLight);
}

void Weapon::setLight(std::shared_ptr<WeaponLight>& weaponLight)
{
	m_weaponLight = weaponLight;
}

float Weapon::getShootingRange() const
{
	return 0.0f;
}
