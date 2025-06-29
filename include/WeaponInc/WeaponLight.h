#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <unordered_set>
#include <vector>
#include <memory>
#include "RayCastClosest.h"
#include "candle/RadialLight.hpp"

class Character; // Forward declaration to avoid circular dependency

class WeaponLight : public candle::RadialLight {
public:
    // Constructor to initialize beam range and angle
    WeaponLight(float range, float beamAngle);

    // Updates light position and rotation each frame
    void update(const sf::Vector2f& position, float rotation);

    // Custom ray casting logic to detect dynamic bodies hit by the light
    

private:
    // Stores hit fixtures detected during custom light casting
    std::unordered_set<b2Fixture*> m_hitFixtures;
};
