#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <memory>  // Required for unique_ptr

#include "VisionLight.h"
#include "WeponInc/WeaponLight.h"
#include "GameObject/Bullet.h"
#include <string>

enum class WeaponType {
    HandGun,
    Shotgun,
    Sniper,
    Rifle
};

//enum class WeaponType {
//	HANDGUN,
//	SHOTGUN,
//	RIFLE,
//    SNIPER,
//};

class Character;
class World;

class Weapon
{
public:
    Weapon(WeaponType);

    std::vector<std::unique_ptr<Bullet>>fire(World& world, const sf::Vector2f& position,
        const sf::Vector2f& direction,Character* owner);

    void update(sf::Vector2f playerPos, float angle, float dt);
    void draw(sf::RenderWindow& window);
    void setLight(std::shared_ptr<WeaponLight>& weaponLight);
    float getShootingRange() const;
	void setShootingRange(float range) { m_shootingRange = range; }
	WeaponType getType() const { return m_type; }

    WeaponLight* getWeaponLight();
    std::shared_ptr<WeaponLight> m_weaponLight;

    static int getPrice(WeaponType type);

protected:
	WeaponType m_type = WeaponType::HandGun; // Default weapon type
    float m_bulletSpeed = 0;

    float m_shootingRange = 0;
    float m_fireCooldown = 1.f;
    float m_fireTimer = 0.f;
};
