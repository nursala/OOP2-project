#pragma once

#include "GameObject/Entity.h"

class World;      // Forward declaration
class Character;  // Forward declaration to avoid circular dependency

class Bullet : public Entity {
public:
    Bullet(World& world, sf::Vector2f& position, sf::Vector2f& direction,
            std::shared_ptr<Character>& owner, float& damage, float& range);
    virtual ~Bullet() override = default;
    void customizeBodyDef(b2BodyDef& bodyDef) override;
    void update(float deltaTime) override;
    std::shared_ptr<Character> getOwnerShared() const;
    virtual b2BodyType getBodyType() const override;
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
    float m_range;
    
	std::weak_ptr<Character> m_owner; // Weak pointer to avoid circular dependency
};
