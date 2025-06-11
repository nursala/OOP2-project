#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "VisionLight.h"
#include "WeaponLight.h"



class Weapon {
public:
    Weapon(b2World& world);

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update(sf::Vector2f playerPos, float angle);
    void draw(sf::RenderWindow& window);
    void setLight(std::shared_ptr<WeaponLight>& weaponLight);


private:
    b2World& m_world;
    std::vector<b2Body*> m_bullets;
    std::shared_ptr<WeaponLight> m_weaponLight;
};
