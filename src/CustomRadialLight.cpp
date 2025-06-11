#include "CustomRadialLight.h"
#include <cmath>
#include <iostream>

CustomRadialLight::CustomRadialLight(b2World& world, sf::Vector2u resolution)
    : m_world(world), m_radius(200.f),
    m_color(sf::Color(255, 255, 200, 200)),
    m_resolution(resolution),
    m_vertices(sf::TriangleFan)
{
    m_vertices.append(sf::Vertex(sf::Vector2f(0.f, 0.f), m_color));

    int segments = 100;
    float step = 2 * 3.14159265f / segments;
    for (int i = 0; i <= segments; ++i) {
        float angle = i * step;
        sf::Vector2f point(std::cos(angle) * m_radius, std::sin(angle) * m_radius);
        m_vertices.append(sf::Vertex(point, m_color));
    }

    if (!m_renderTexture.create(resolution.x, resolution.y)) {
        std::cerr << "Failed to create light render texture.\n";
    }

    if (!m_shader.loadFromFile("light.frag", sf::Shader::Fragment)) {
        std::cerr << "Failed to load shader.\n";
    }

    m_sprite.setTexture(m_renderTexture.getTexture());
    m_sprite.setColor(sf::Color::White);
}

void CustomRadialLight::setRadius(float radius) {
    m_radius = radius;
}

void CustomRadialLight::setColor(const sf::Color& color) {
    m_color = color;
}

void CustomRadialLight::setLightDirection(float angleInDegrees, float fovInDegrees) {
    m_angle = angleInDegrees * 3.14159265f / 180.f;
    m_fov = fovInDegrees * 3.14159265f / 180.f;
}

void CustomRadialLight::setPosition(const sf::Vector2f& pos) {
    m_position = pos;
    setOrigin(0.f, 0.f);
}

void CustomRadialLight::update() {
    updateShader();
}

void CustomRadialLight::updateShader() {
    m_shader.setUniform("lightPos", m_position);
    m_shader.setUniform("lightRadius", m_radius);
    m_shader.setUniform("directionAngle", m_angle);
    m_shader.setUniform("fov", m_fov);
    m_shader.setUniform("resolution", sf::Glsl::Vec2(m_resolution));

    m_renderTexture.clear(sf::Color::Transparent);
    sf::RenderStates states;
    states.shader = &m_shader;
    states.transform = getTransform();
    m_renderTexture.draw(m_vertices, states);
    m_renderTexture.display();
}

void CustomRadialLight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
