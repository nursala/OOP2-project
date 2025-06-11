
#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <unordered_set>
#include "RayCastClosest.h"
#include "candle/RadialLight.hpp"

class VisionLight : public candle::RadialLight {
public:
    VisionLight(float range, float beamAngle);

    void update(const sf::Vector2f& position, float rotation);

    void castLightCustom(const candle::EdgeVector::iterator& begin, const candle::EdgeVector::iterator& end, b2World& world, std::unordered_set<b2Fixture*>& hitFixtures);
    

};
