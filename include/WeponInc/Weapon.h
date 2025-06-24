#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <memory>  // Required for unique_ptr

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



class Character;
class World;
class RenderLayers;

class Weapon
{
public:
   
    Weapon();

    std::unique_ptr<Bullet> fire(World& world, const sf::Vector2f& position,
        const sf::Vector2f& direction, Character* owner);

    void update(sf::Vector2f playerPos, float angle, float dt);
    void draw(sf::RenderWindow& window);
    void draw(RenderLayers& renderLayers);
    float getShootingRange() const;

    WeaponLight* getWeaponLight();


protected:
    float m_bulletSpeed = 0;
    std::unique_ptr<WeaponLight> m_weaponLight;

    float m_shootingRange = 0;
    float m_fireCooldown = 1.f;
    float m_fireTimer = 0.f;
};
