#pragma once

#include "GameObject/Entity.h"

class World;      // Forward declaration
class Character;  // Forward declaration to avoid circular dependency

class Bullet : public Entity {
public:
    Bullet(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, Character* owner, float damage);

    void customizeBodyDef(b2BodyDef& bodyDef) override;
    void update(float deltaTime) override;
    virtual b2BodyType getBodyType() const override;

    bool shouldDestroy() const;

    Character* getOwner() const { return m_owner; }  // Getter for owner
    float getDamage() const;
    void setDamage(float damage);

private:
    void customizeFixtureDef(b2FixtureDef& fixtureDef) override;

    sf::Vector2f m_direction;
    float m_speed;
    float m_lifetime = 0.f;
    const float MAX_LIFETIME = 0.5f;
    bool m_destroy = false;
    float m_damage;

    sf::CircleShape m_shape;

    Character* m_owner = nullptr;  // NEW: Pointer to the creator (player/enemy)
};
