#include "VisionLight.h"
#include <cmath>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"

// البناء
VisionLight::VisionLight(float range, float beamAngle)
    : candle::RadialLight() {
    setRange(range);
	setFade(true); // تفعيل التلاشي
	setIntensity(1.0f); // تعيين شدة الضوء
    setBeamAngle(beamAngle);
    setColor(sf::Color(255, 255, 255, 200)); // لون شفاف للرؤية
}

// تحديث موقع وزاوية الضوء
void VisionLight::update(const sf::Vector2f& position, float rotation) {
    setPosition(position);
    setRotation(rotation);
}
