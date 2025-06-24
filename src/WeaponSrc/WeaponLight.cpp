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

// Custom raycast to detect dynamic bodies in beam cone
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

// Returns closest visible enemy (if self is player) or player (if self is enemy)
Character* WeaponLight::getClosestTarget(const Character* self) {
   
    Character* closestCharacter = nullptr;
    float minDistSq = std::numeric_limits<float>::max();
    sf::Vector2f lightPos = getPosition();

    bool lookingForEnemy = dynamic_cast<const Player*>(self);

    for (auto* fixture : m_hitFixtures) {
        b2Body* body = fixture->GetBody();
        auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);

        if (!character || !character->isVisible()) continue;

        if (lookingForEnemy) {
            auto* enemy = dynamic_cast<Enemy*>(character);
            if (!enemy || enemy->isSpy()) continue; // Skip spies
        }
        else {
            if (!dynamic_cast<Player*>(character)) continue;
        }

        sf::Vector2f charPos = character->getPosition();
        float dx = charPos.x - lightPos.x;
        float dy = charPos.y - lightPos.y;
        float distSq = dx * dx + dy * dy;

        if (distSq < minDistSq) {
            minDistSq = distSq;
            closestCharacter = character;
        }
    }

    m_hitFixtures.clear();
    return closestCharacter;
}

// Returns all valid targets in beam cone
std::vector<std::shared_ptr<Character>> WeaponLight::getAllTargets(const Character* self) {
    std::vector<std::shared_ptr<Character>> targets;
    sf::Vector2f lightPos = getPosition();
    bool lookingForEnemy = dynamic_cast<const Player*>(self);

    for (auto* fixture : m_hitFixtures) {
        b2Body* body = fixture->GetBody();
        auto* rawPtr = reinterpret_cast<Character*>(body->GetUserData().pointer);

        // Wrap in shared_ptr only if valid and visible
        if (!rawPtr || !rawPtr->isVisible())
            continue;

        if (lookingForEnemy) {
            auto* enemy = dynamic_cast<Enemy*>(rawPtr);
            if (!enemy || enemy->isSpy()) continue; // Ignore spies
        }
        else {
            if (!dynamic_cast<Player*>(rawPtr)) continue;
        }

        targets.emplace_back(std::shared_ptr<Character>(rawPtr, [](Character*) {}));
    }

    m_hitFixtures.clear();
    return targets;
}
