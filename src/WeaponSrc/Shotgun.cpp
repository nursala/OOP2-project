#include "WeaponInc/Shotgun.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"
#include "Factory.h"

Shotgun::Shotgun() : Weapon(Constants::WeaponType::Shotgun, 150.f, 8.f, 60.f)
{
	m_fireCooldown = 1.f; // Set the cooldown for firing
}

std::vector<std::unique_ptr<Bullet>> Shotgun::fire(World& world, const b2Vec2& position, 
                            const sf::Vector2f& direction, std::shared_ptr<Character> owner)
{
    std::vector<std::unique_ptr<Bullet>> bullets;
    if (m_fireTimer > 0.f)
        return bullets;

    m_fireTimer = m_fireCooldown;

    std::vector<float> angles = { 0.f, -20.f, 20.f };

    for (float angleDeg : angles)
    {
        float angleRad = angleDeg * 3.14159f / 180.f;

        sf::Vector2f dirRotated = {
            direction.x * std::cos(angleRad) - direction.y * std::sin(angleRad),
            direction.x * std::sin(angleRad) + direction.y * std::cos(angleRad)
        };

        auto bullet = Factory::instance().createAs<Bullet>(
            Constants::EntityType::Bullet,
            world,
            position,
            dirRotated,
            owner,
            m_damage,
            m_weaponLight->getRange()
        );

        bullets.push_back(std::move(bullet));
    }

    return bullets;
}


