#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "AnimationInc/Animation.h"
//Entity.h
class Entity {
public:
    Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual void update(float deltaTime) = 0;  
    virtual void render(sf::RenderWindow& window);
    b2Vec2 getPosition() const;
    sf::Vector2f getPixels() const;
    void setPostion(const b2Vec2& position);
    virtual ~Entity() = default;
	void setVelocity(const b2Vec2& velocity);
	b2Vec2 getVelocity() const;
    b2Body* getBody() const;

protected:
    b2Body* m_body;
    sf::Sprite m_sprite;
    Animation m_animation;
	b2Vec2 m_velocity;  // سرعة الكائن
	sf::RectangleShape m_hitbox; // صندوق الاصطدام

    static constexpr float SCALE = 30.f;
};
