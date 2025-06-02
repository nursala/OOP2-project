#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class LightSystem {
public:
    LightSystem(float lightRadius = 100.f, int rayCount = 100);

    void update(const sf::Vector2f& origin, float directionAngle, float fov, b2World& world);

    void draw(sf::RenderTarget& target) const;

    const sf::Sprite& getShadowSprite() const { return shadowSprite; }

private:
    float LIGHT_RADIUS;
    int RAY_COUNT;

    sf::VertexArray lightCone;
    sf::RenderTexture shadowTexture;
    sf::Sprite shadowSprite;
};
