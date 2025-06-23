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
    void castLightCustom(
        const candle::EdgeVector::iterator& begin,
        const candle::EdgeVector::iterator& end,
        b2World& world
    );

    // Returns the closest visible valid target (enemy if called from player, player if from enemy)
    Character* getClosestTarget(const Character* self);

    // Returns all valid visible targets in light cone (ignores spies if self is player)
    std::vector<std::shared_ptr<Character>> getAllTargets(const Character* self);

private:
    // Stores hit fixtures detected during custom light casting
    std::unordered_set<b2Fixture*> m_hitFixtures;
};
