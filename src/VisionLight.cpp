#include "VisionLight.h"
#include <cmath>

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

void VisionLight::castLightCustom(
    const candle::EdgeVector::iterator& begin,
    const candle::EdgeVector::iterator& end,
    b2World& world,
    std::unordered_set<b2Fixture*>& hitFixtures)
{
    this->castLight(begin, end); // استدعاء الدالة الأصلية للرسم
    hitFixtures.clear();

    float startAngle = getRotation() - getBeamAngle() / 2.f;
    float endAngle = getRotation() + getBeamAngle() / 2.f;

    const int rayCount = 100;
    float angleStep = (endAngle - startAngle) / static_cast<float>(rayCount);

    sf::Vector2f lightPos = getPosition();
    b2Vec2 origin(lightPos.x / 30.f, lightPos.y / 30.f);  // تحويل للمتر

    for (int i = 0; i <= rayCount; ++i) {
        float angleDeg = startAngle + i * angleStep;
        float angleRad = angleDeg * b2_pi / 180.f;
        b2Vec2 direction(std::cos(angleRad), std::sin(angleRad));
        b2Vec2 endPoint = origin + (getRange() / 30.f) * direction;

        RayCastClosest callback;
        world.RayCast(&callback, origin, endPoint);

        if (callback.hit() && callback.getFixture()) {
            b2Body* body = callback.getFixture()->GetBody();
            if (body->GetType() == b2_dynamicBody) {
                hitFixtures.insert(callback.getFixture());
            }
        }
    }
}
