#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class CustomRadialLight : public sf::Drawable, public sf::Transformable {
public:
    CustomRadialLight(b2World& world, sf::Vector2u resolution);

    void setRadius(float radius);
    void setColor(const sf::Color& color);
    void setLightDirection(float angleInDegrees, float fovInDegrees);
    void setPosition(const sf::Vector2f& pos);
    void update();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateShader();

    b2World& m_world;
    float m_radius;
    float m_angle = 0.f;
    float m_fov = 60.f;
    sf::Color m_color;
    sf::Vector2f m_position;
    sf::Vector2u m_resolution;

    sf::Shader m_shader;
    sf::RenderTexture m_renderTexture;
    sf::Sprite m_sprite;
    sf::VertexArray m_vertices;
};
