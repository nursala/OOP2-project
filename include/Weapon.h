#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "VisionLight.h"

class Weapon {
public:
    Weapon(b2World& world, const sf::Vector2f& origin);

    void fire(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);
	VisionLight& getVisionLight() {
		return m_visionLight;
	}

private:
    b2World& m_world;
	sf::RectangleShape m_shape; // For rendering the weapon
    std::vector<b2Body*> m_bullets;
    VisionLight m_visionLight;

};
