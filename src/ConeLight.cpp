#include "ConeLight.h"

constexpr float DEG2RAD = 3.14159265f / 180.f;

ConeLight::ConeLight(float range, float angle, int resolution)
    : m_range(range),
    m_angle(angle),
    m_resolution(resolution),
    m_centerColor(sf::Color(255, 255, 200, 150)),
    m_edgeColor(sf::Color(255, 255, 200, 0)),
    m_vertices(sf::TriangleFan)
{
    rebuild();
}

void ConeLight::setRange(float range) {
    m_range = range;
    rebuild();
}

void ConeLight::setAngle(float angle) {
    m_angle = angle;
    rebuild();
}

void ConeLight::setResolution(int resolution) {
    m_resolution = resolution;
    rebuild();
}

void ConeLight::setColor(const sf::Color& color) {
	m_centerColor = color;
	m_edgeColor = sf::Color(color.r, color.g, color.b, 0); // edge color with alpha 0
	rebuild();
}


void ConeLight::setRotation(float degrees) {
    sf::Transformable::setRotation(degrees); // ✅ حل المشكلة
    rebuild();
}


void ConeLight::update() {
    rebuild(); // يمكن تحسين الأداء بتحديث فقط عند تغير الموقع أو الدوران
}

void ConeLight::rebuild() {
    m_vertices.clear();
    m_vertices.append(sf::Vertex(sf::Vector2f(0.f, 0.f), m_centerColor));

    float half = m_angle / 2.f;
    float step = m_angle / static_cast<float>(m_resolution);

    for (int i = 0; i <= m_resolution; ++i) {
        float angle = (-half + i * step + getRotation()) * DEG2RAD;
        float x = std::cos(angle) * m_range;
        float y = std::sin(angle) * m_range;
        m_vertices.append(sf::Vertex(sf::Vector2f(x, y), m_edgeColor));
    }
}

void ConeLight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.blendMode = sf::BlendAdd;
    target.draw(m_vertices, states);
}
