#pragma once

#include "GameObject/Entity.h"
#include "candle/RadialLight.hpp"
#include "Constants.h"

// Forward declarations
class Player;
class Enemy;
class Bullet;
class Gift;

// Description: Represents a static gift entity that glows with pulsing light
//              and interacts with the player to apply powerups.

class Gift : public Entity {
public:
    // Constructor
    Gift(World& world, const b2Vec2& position);

    // Return the type of the gift
    Constants::GiftType getType() const;

    // Update pulse and light state
    void update(const float deltaTime) override;

    // Render light and sprite
    void render(RenderLayers& renderLayers);

    // Mark the gift as destroyed
    void des();

    // ==================== Double Dispatch ====================
    virtual Constants::EntityType getEntityType() const override { return m_entityType; }
    void onCollide(Entity& other) override;
    void onCollideWith(Player& player) override;
    void onCollideWith(Enemy&) override {}
    void onCollideWith(Bullet&) override {}
    void onCollideWith(Gift&) override {}

private:
    Constants::GiftType m_type;          // Type of gift (e.g., health, armor, etc.)
    candle::RadialLight m_radialLight;  // Light effect for the gift
    float m_pulseTime = 0.f;             // Internal timer for pulsing light

    // Customize fixture to act as sensor only
    void customizeFixtureDef(b2FixtureDef& fixtureDef) override;

    // Return static body type
    virtual b2BodyType getBodyType() const override { return b2_staticBody; }
    Constants::GiftType genrateType();
};
