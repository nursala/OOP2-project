#include "VisionLight.h"
#include <cmath>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"

//------------------------------
// VisionLight Ctor
VisionLight::VisionLight(const float range, const float beamAngle)
    : candle::RadialLight() {
    setRange(range);
	setFade(true);
	setIntensity(1.0f); 
    setBeamAngle(beamAngle);
    setColor(sf::Color(255, 255, 255, 200)); 
}

//------------------------------
// Update the light's position and rotation based on the character's position and rotation
void VisionLight::update(const sf::Vector2f& position, const float rotation) {
    setPosition(position);
    setRotation(rotation);
}
