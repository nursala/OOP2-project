//==============================================
// Description: Abstract base class for all characters (players/enemies)
//==============================================

#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "StatesInc/State.h"
#include "Bars/HealthBar.h"
#include "Bars/ArmorBar.h"

#include <box2d/b2_fixture.h>
#include <unordered_set>
#include <memory>

class Weapon;
class VisionLight;

class Character : public Entity, public std::enable_shared_from_this<Character>
{
public:
    //==========================
    // Constructor / Destructor
    //==========================
    Character(World& world, const b2Vec2& positionB2);
    virtual ~Character() override = default;

    //==========================
    // Main Loop
    //==========================
    virtual void update(const float deltaTime);
    void render(RenderLayers& renderLayers);
    virtual b2BodyType getBodyType() const override;
    void move(const float dt);

    //==========================
    // Combat & State
    //==========================
    virtual void shoot();
    virtual void takeDamage(const int amount) = 0;
    virtual Character* getClosestTarget() = 0;

    //==========================
    // Getters / Setters
    //==========================
    float getShootingRange() const;
    void setShootingRange(const float range);
    void setRotation(const float angle);
    float getSpeed() const { return m_speed; }

    void setTarget(std::shared_ptr<Character> target) { m_target = target; }
    std::shared_ptr<Character> getTarget() const { return m_target.lock(); }

    Animation& getAnimation() const { return *m_animation; }
    sf::Sprite& getSprite() { return m_sprite; }
    Weapon* getWeapon();

    virtual void rotateTowardMouse(sf::RenderWindow&) {}

protected:
    //==========================
    // Basic Attributes
    //==========================
    float m_speed = 0.f;
    float m_health = 100.f;
    float m_visableTime = 0.1f;

    //==========================
    // Components
    //==========================
    std::unique_ptr<State> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    std::unique_ptr<HealthBar> m_healthBar;
    std::unique_ptr<Animation> m_animation;
    std::unique_ptr<VisionLight> m_visionLight;

    //==========================
    // Targeting
    //==========================
    std::weak_ptr<Character> m_target;
    std::unordered_set<b2Fixture*> m_hitFixtures;
private:
    void updateTargets();
};
