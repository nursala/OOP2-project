#include "WeaponInc/Shotgun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

Shotgun::Shotgun() : Weapon(Constants::WeaponType::Shotgun, 150.f, 7.f, 60.f)
{
}

std::vector<std::unique_ptr<Bullet>> Shotgun::fire(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, std::shared_ptr<Character> owner)
{
	std::vector<std::unique_ptr<Bullet>> bullets;
	if (m_fireTimer > 0.f)
		return bullets;

	m_fireTimer = m_fireCooldown;
	
	// Shotgun logic - fire one bullet straight and two bullets at angles
	// Straight bullet
	bullets.push_back(std::make_unique<Bullet>(world, position, direction, owner, m_damage, m_shootingRange));

	// Left bullet (20 degrees counterclockwise)
	float leftAngle = -20.f * 3.14159f / 180.f; // Convert to radians
	sf::Vector2f leftDir = sf::Vector2f(
		direction.x * std::cos(leftAngle) - direction.y * std::sin(leftAngle),
		direction.x * std::sin(leftAngle) + direction.y * std::cos(leftAngle)
	);
	bullets.push_back(std::make_unique<Bullet>(world, position, leftDir, owner, m_damage, m_shootingRange));

	// Right bullet (20 degrees clockwise)
	float rightAngle = 20.f * 3.14159f / 180.f; // Convert to radians
	sf::Vector2f rightDir = sf::Vector2f(
		direction.x * std::cos(rightAngle) - direction.y * std::sin(rightAngle),
		direction.x * std::sin(rightAngle) + direction.y * std::cos(rightAngle)
	);
	bullets.push_back(std::make_unique<Bullet>(world, position, rightDir, owner, m_damage, m_shootingRange));
	
	return bullets;
}
