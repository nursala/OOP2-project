#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include "VisionLight.h"
#include "WeponInc/WeaponLight.h"
#include "GameObject/Bullet.h"
#include <string>

//enum class WeaponType {
//    BasicGun,
//    Shotgun,
//    Sniper,
//    Laser
//};


class Weapon
{
public:
   
    Weapon() = default;

    std::unique_ptr<Bullet> fire(World& world, const sf::Vector2f& position,
        const sf::Vector2f& direction);
    void update(sf::Vector2f playerPos, float angle, float dt);
    void draw(sf::RenderWindow& window);
    void setLight(std::shared_ptr<WeaponLight>& weaponLight);
    float getShootingRange() const;

    WeaponLight* getWeaponLight();

    //static int getPrice(WeaponType type);

protected:
    std::shared_ptr<WeaponLight> m_weaponLight;

    float m_bulletSpeed = 0;
    float m_shootingRange = 0;
    float m_fireCooldown = 1.f;
    float m_fireTimer = 0.f;
};
