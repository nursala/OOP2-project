
#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <unordered_set>
#include "RayCastClosest.h"
#include "candle/RadialLight.hpp"
#include "GameObject/Character.h"

class VisionLight : public candle::RadialLight {
public:
    VisionLight(float range, float beamAngle);

    void update(const sf::Vector2f& position, float rotation);

private:
	std::unordered_set<b2Fixture*> m_hitFixtures; 
};
