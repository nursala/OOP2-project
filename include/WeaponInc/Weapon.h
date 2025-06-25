#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <memory>  // Required for unique_ptr

#include "VisionLight.h"
#include "WeaponInc/WeaponLight.h"
#include "GameObject/Bullet.h"
#include <string>

enum class WeaponType {
    HandGun,
    Shotgun,
    Sniper,
    Rifle
};

class Character;
class World;
class RenderLayers;

class Weapon
{
public:

    virtual std::vector<std::unique_ptr<Bullet>>fire(World& world, const sf::Vector2f& position,
        const sf::Vector2f& direction,Character* owner);

    

    void update(sf::Vector2f playerPos, float angle, float dt);
    void draw(sf::RenderWindow& window);
    void draw(RenderLayers& renderLayers);
    float getShootingRange() const;
	void setShootingRange(float range) { m_shootingRange = range; }
	WeaponType getType() const { return m_type; }

    WeaponLight* getWeaponLight();

    static int getPrice(WeaponType type);

    float getDamage() const;
    void setDamage(float damage);

protected:
    Weapon(WeaponType, float shootingRange, float damage, float angle);
	WeaponType m_type;
    float m_bulletSpeed;
    std::unique_ptr<WeaponLight> m_weaponLight;

    float m_shootingRange;
    float m_fireCooldown = 1.f;
    float m_fireTimer = 0.f;
    float m_damage;

};
