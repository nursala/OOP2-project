#include "LightSystem.h"
#include "RayCastClosest.h"
#include <cmath>
#include <GameObject/Enemy.h>

constexpr float SCALE = 30.f; // 1 متر = 30 بكسل


LightSystem::LightSystem(float lightRadius, int rayCount )
    : LIGHT_RADIUS(lightRadius), RAY_COUNT(rayCount), lightCone(sf::TriangleFan)
{
    shadowTexture.create(1280, 720);
    shadowSprite.setTexture(shadowTexture.getTexture());
}

void LightSystem::update(const sf::Vector2f& origin, float directionAngle, float fov, b2World& world) {
    lightCone.clear();
    lightCone.append(sf::Vertex(origin, sf::Color(255, 255, 100, 180)));

    float px = origin.x / SCALE;
    float py = origin.y / SCALE;

    for (int i = 0; i <= RAY_COUNT; ++i) {
        float angle = directionAngle - fov / 2.f + fov * i / RAY_COUNT;
        float dx = std::cos(angle) / SCALE;
        float dy = std::sin(angle) / SCALE;

        b2Vec2 start(px, py);
        b2Vec2 end(px + dx * LIGHT_RADIUS, py + dy * LIGHT_RADIUS);

        RayCastClosest callback;
        world.RayCast(&callback, start, end);

        sf::Vector2f hitPoint;
        if (callback.hit()) {
            b2Fixture* fixture = callback.getFixture();
            if (fixture) {
                /*Enemy* enemy = reinterpret_cast<Enemy*>(fixture->GetUserData().pointer);
                if (enemy) {
                    enemy->onLightCollision();
                }*/
            }
            hitPoint.x = callback.getPoint().x * SCALE;
            hitPoint.y = callback.getPoint().y * SCALE;
        }

        else {
            hitPoint.x = end.x * SCALE;
            hitPoint.y = end.y * SCALE;
        }

        lightCone.append(sf::Vertex(hitPoint, sf::Color(255, 255, 100, 10)));
    }

    shadowTexture.clear(sf::Color(0, 0, 0, 200));
    sf::RenderStates noBlend;
    noBlend.blendMode = sf::BlendNone;
    shadowTexture.draw(lightCone, noBlend);
    shadowTexture.display();
    shadowSprite.setTexture(shadowTexture.getTexture());
}

void LightSystem::draw(sf::RenderTarget& target) const {
    target.draw(shadowSprite);
}
