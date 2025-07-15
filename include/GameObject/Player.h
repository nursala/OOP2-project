// Player.h
// Authors: [Your Name]
// ID: [Your ID]
// Login: [Your Login]
// Description: Player class derived from Character. Handles player-specific logic like input, damage, upgrades.

#pragma once

#include "GameObject/Character.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "Bars/HealthBar.h"
#include "Bars/ArmorBar.h"
#include "WeaponInc/Weapon.h"
#include "VisionLight.h"

#include <unordered_map>
#include <functional>

class World;
class Gift;
class Bullet;

class Player : public Character {
public:
    // Constructor: Initializes the player with position and world context
    Player(World& world, const b2Vec2& position);

    // Destructor
    virtual ~Player() override = default;

    // Updates the player logic each frame
    void update(const float deltaTime) override;

    // Applies damage to the player (considers armor first)
    void takeDamage(int damage) override;

    // Heals the player (capped at 100)
    void addHealth();

    // Adds armor to the player (capped at 50)
    void addArmor();

    // Boosts the player's speed temporarily
    void addSpeed();

    // Temporarily increases the vision range
    void increaseVisionTemporarily(const float extraRange, const float duration);

    // Rotates player sprite toward the mouse
    void rotateTowardMouse(sf::RenderWindow& window) override;

    // Renders the player (calls base + draws armor bar)
    void render(RenderLayers& layers) override;

    // Checks if the player is still alive
    bool isAlive() const { return m_alive; }

    //==================== Collision Dispatch Support ====================//
    Constants::EntityType getEntityType() const override { return Constants::EntityType::Player; }
    void onCollide(Entity& other) override;
    void onCollideWith(Gift& gift) override;
    void onCollideWith(Bullet& bullet) override;

private:
    // Returns the closest target visible to the player
    void getClosestTarget() override;


    // Armor bar UI element
    std::unique_ptr<ArmorBar> m_armorBar;

    // Current armor value (0-50)
    float m_armor = 50.f;

    // Player alive state
    bool m_alive = true;

    // Vision boost flag
    bool m_visionBoostActive = false;

    // Remaining vision boost time
    float m_visionBoostTimer = 0.f;

    // Stores the original vision range before boosting
    float m_originalVisionRange = 0.f;

    //==================== Collision Gift Handling ====================//
    using GiftHandler = std::function<void(Gift&)>;
    std::unordered_map<Constants::GiftType, GiftHandler> m_giftHandlers;
    void initGiftHandlers();
};
