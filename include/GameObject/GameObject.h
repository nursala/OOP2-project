#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject(b2World* world, const b2Vec2& position);
    virtual ~GameObject();

    b2Body* getBody() const;
    b2Vec2 getPosition() const;
    void setPosition(const b2Vec2& position);
    void setTexture(std::shared_ptr<sf::Texture> texture);
    virtual void render(sf::RenderTarget& target);
    virtual void update(float deltaTime) = 0;

    // Add a method to create a fixture (collision shape)
    virtual void createFixture(const b2Shape& shape, float density = 1.0f);

    // For collision identification
    void setUserData(void* data);
    void* getUserData() const;

protected:
    b2Body* m_body;
    sf::Sprite m_sprite;
};
