#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "VisionLight.h"
#include "WeaponLight.h"
#include "GameObject/Bullet.h"

class Weapon {
public:
    Weapon() = default;

    std::unique_ptr<Bullet> fire(World& world, const sf::Vector2f& position,
                                const sf::Vector2f& direction);
    void update(sf::Vector2f playerPos, float angle);
    void draw(sf::RenderWindow& window);
    void setLight(std::shared_ptr<WeaponLight>& weaponLight);
	float getShootingRange() const;
private:
    std::shared_ptr<WeaponLight> m_weaponLight;
    float m_shootingRange = 0;
};
