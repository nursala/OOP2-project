// CustomLight.cpp
#include "CustomLight.h"
#include <cmath>

namespace {
    constexpr float PI = 3.14159265f;
    constexpr float DEG2RAD = PI / 180.f;
}

CustomLight::CustomLight(b2World& world)
    : m_vertices(sf::TriangleFan), m_world(world), m_range(200.f), m_angle(60.f), m_resolution(60), m_color(sf::Color(255, 255, 200, 200)) {
    m_vertices.append(sf::Vertex(sf::Vector2f(0.f, 0.f), m_color));
    updateRays();
}

void CustomLight::setRange(float r) {
    m_range = r;
    updateRays();
}

void CustomLight::setAngle(float deg) {
    m_angle = deg;
    updateRays();
}

void CustomLight::setResolution(int rays) {
    m_resolution = rays;
    updateRays();
}

void CustomLight::updateRays() {
    m_vertices.resize(1); // center point only
    b2Vec2 origin(getPosition().x, getPosition().y);

    float halfAngle = m_angle / 2.f;
    float step = m_angle / static_cast<float>(m_resolution);

    for (int i = 0; i <= m_resolution; ++i) {
        float angleDeg = -halfAngle + step * i + getRotation();
        float angleRad = angleDeg * DEG2RAD;

        b2Vec2 dir(std::cos(angleRad), std::sin(angleRad));
        b2Vec2 end = origin + m_range * dir;

        RayCastClosest callback;
        m_world.RayCast(&callback, origin, end);

        b2Vec2 hit = callback.hit() ? callback.getPoint() : end;
        sf::Vector2f point(hit.x, hit.y);

        m_vertices.append(sf::Vertex(point, m_color));
    }
}

void CustomLight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vertices, states);
}