#include "WeaponInc/WeaponLight.h"
#include <cmath>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Character.h"
#include <iostream>
#include <memory>

WeaponLight::WeaponLight(float range, float beamAngle)
    : candle::RadialLight()
{
    setRange(range);
    setFade(true);
    setIntensity(1.0f);
    setBeamAngle(beamAngle);
    setColor(sf::Color(255, 255, 255, 200));
}

// Updates light position and direction
void WeaponLight::update(const sf::Vector2f& position, float rotation) {
    setPosition(position);
    setRotation(rotation);
}

