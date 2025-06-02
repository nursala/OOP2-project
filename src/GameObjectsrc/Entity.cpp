#include "GameObject/Entity.h"

Entity::Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
    sf::Vector2u imageCount, float switchTime)
    : m_animation(texture, imageCount, switchTime)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / 30, position.y/ 30);
    m_body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(25.f / SCALE, 25.f / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_body->CreateFixture(&fixtureDef);

    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(m_animation.getUvRect());
}

void Entity::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}
