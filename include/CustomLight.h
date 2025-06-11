// CustomLight.h
#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "RayCastClosest.h"

class CustomLight : public sf::Drawable, public sf::Transformable {
public:
    CustomLight(b2World& world);

    void setRange(float r);
    void setAngle(float deg);
    void setResolution(int rays);
    void updateRays();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    b2World& m_world;
    float m_range;
    float m_angle;
    int m_resolution;
    sf::Color m_color;
    sf::VertexArray m_vertices;
};
