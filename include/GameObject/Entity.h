#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "AnimationInc/Animation.h"

class Entity {
public:
    Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual void update(float deltaTime) = 0;  
    virtual void render(sf::RenderWindow& window);
    virtual ~Entity() = default;

protected:
    b2Body* m_body;
    sf::Sprite m_sprite;
    Animation m_animation;

    static constexpr float SCALE = 30.f;
};
