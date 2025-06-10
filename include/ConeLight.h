#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class ConeLight : public sf::Drawable, public sf::Transformable {
public:
    ConeLight(float range = 200.f, float angle = 60.f, int resolution = 600);

    void setRange(float range);
    void setAngle(float angle);
    void setResolution(int resolution);
    void setRotation(float degrees);
    void update();
    void rebuild();
    void setColor(const sf::Color& color);


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float m_range;
    float m_angle;
    int m_resolution;
    sf::Color m_centerColor;
    sf::Color m_edgeColor;
    sf::VertexArray m_vertices;
};
