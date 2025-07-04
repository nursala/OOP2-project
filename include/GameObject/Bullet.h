#pragma once

#include "GameObject/Entity.h"
#include <memory>

class World;      // Forward declaration
class Character;  // Forward declaration to avoid circular dependency

// Description: Represents a bullet shot by a character in the world.
//              Handles movement, damage, range, and destruction.

class Bullet : public Entity {
public:
    // Constructor
    Bullet(World& world, const b2Vec2& position, const sf::Vector2f& direction,
        const std::shared_ptr<Character>& owner, const float& damage, const float& range);

    // Destructor
    virtual ~Bullet() override = default;

    // Returns the type of body (kinematic)
    virtual b2BodyType getBodyType() const override;

    // Updates bullet position and checks for destruction
    void update(const float deltaTime) override;

    // Returns the character that owns the bullet
    std::shared_ptr<Character> getOwnerShared() const;

    // Returns the bullet's damage
    float getDamage() const;

private:
    // Customize Box2D body definition
    void customizeBodyDef(b2BodyDef& bodyDef) override;

    // Customize Box2D fixture definition
    void customizeFixtureDef(b2FixtureDef& fixtureDef) override;

private:
    sf::Vector2f m_direction;            // Movement direction
    float m_speed = 15.f;                // Bullet speed
    float m_damage = 0.f;                // Bullet damage
    float m_range = 0.f;                 // Max range before destruction

    bool m_destroy = false;              // Internal flag for destruction

    std::weak_ptr<Character> m_owner;    // Owner (shooter) of the bullet
};
