#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <memory>  
#include "VisionLight.h"
#include "WeaponInc/WeaponLight.h"
#include "GameObject/Bullet.h"
#include <string>
#include "Constants.h"

class Character;
class World;
class RenderLayers;

class Weapon
{
public:
    virtual ~Weapon() = default; // Add a virtual destructor

    virtual std::vector<std::unique_ptr<Bullet>> fire(World& world, const b2Vec2& position,
        const sf::Vector2f& direction, std::shared_ptr<Character> owner);

    void update(sf::Vector2f playerPos, float angle, float dt);
    void draw(RenderLayers& renderLayers);
    float getShootingRange() const;
    void setShootingRange(float range) { m_shootingRange = range; }
    Constants::WeaponType getType() const { return m_type; }

    WeaponLight* getWeaponLight();

    float getFireTimer() const;

    void setFireCooldown(float cooldown) { m_fireCooldown = cooldown; }
    void setBulletSpeed(float speed) { m_bulletSpeed = speed; };

protected:
    Weapon(Constants::WeaponType, float shootingRange, float damage, float angle);
    Constants::WeaponType m_type;
    float m_bulletSpeed;
    std::unique_ptr<WeaponLight> m_weaponLight;

    float m_shootingRange;
    float m_fireCooldown;
    float m_fireTimer = 0.f;
    float m_damage;
};
