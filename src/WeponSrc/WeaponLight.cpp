#include "WeponInc/WeaponLight.h"
#include <cmath>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Character.h"

WeaponLight::WeaponLight(float range, float beamAngle)
    : candle::RadialLight() 
{
    setRange(range);
    setFade(true); // تفعيل التلاشي
    setIntensity(1.0f); // تعيين شدة الضوء
    setBeamAngle(beamAngle);
    setColor(sf::Color(255, 255, 255, 200)); // لون شفاف للرؤية
}

// تحديث موقع وزاوية الضوء
void WeaponLight::update(const sf::Vector2f& position, float rotation) {
    setPosition(position);
    setRotation(rotation);
}

void WeaponLight::castLightCustom(
    const candle::EdgeVector::iterator& begin,
    const candle::EdgeVector::iterator& end,
    b2World& world)
{
    m_hitFixtures.clear();
    this->castLight(begin, end); 

    float startAngle = getRotation() - getBeamAngle() / 2.f;
    float endAngle = getRotation() + getBeamAngle() / 2.f;

    const int rayCount = 100;
    float angleStep = (endAngle - startAngle) / static_cast<float>(rayCount);

    sf::Vector2f lightPos = getPosition();
    b2Vec2 origin(lightPos.x / 30.f, lightPos.y / 30.f);  

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
                m_hitFixtures.insert(callback.getFixture());
            }
        }
    }
}

Character* WeaponLight::getClosestTarget(const Character* self) {
    Character* closestCharacter = nullptr;
    float minDistSq = std::numeric_limits<float>::max();
    sf::Vector2f lightPos = getPosition();

    bool lookingForEnemy = dynamic_cast<const Player*>(self);

    for (auto* fixture : m_hitFixtures) {
        b2Body* body = fixture->GetBody();
        if (auto* charater = reinterpret_cast<Character*>(body->GetUserData().pointer)) {
            if (!charater->isVisible())
                continue;

            if (lookingForEnemy && !dynamic_cast<Enemy*>(charater))
                continue;
            if (!lookingForEnemy && !dynamic_cast<Player*>(charater))
                continue;

            sf::Vector2f charaterPos = charater->getPosition();
            float dx = charaterPos.x - lightPos.x;
            float dy = charaterPos.y - lightPos.y;
            float distSq = dx * dx + dy * dy;

            if (distSq < minDistSq) {
                minDistSq = distSq;
                closestCharacter = charater;
            }
        }
    }

    m_hitFixtures.clear();
    return closestCharacter;
}
