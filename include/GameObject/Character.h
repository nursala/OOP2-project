// Character.h

#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include "ArmorBar.h"

class Weapon;
class World;
class RenderLayers;
class VisionLight;

class Character : public Entity
{
public:
    Character(World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual ~Character() = default;

    virtual void update(float );
    void render(sf::RenderWindow& ) override;
    void update(float deltaTime);
    void render(sf::RenderWindow& window) override;
    void render(RenderLayers& renderLayers);
    const MoveInfo& getLastMoveInfo();
    virtual b2BodyType getBodyType() const override;
    void move(float dt);

    virtual void takeDamage(int ) = 0;
    virtual void shoot(float );

    float getShootingRange() const;
    void setShootingRange(float );
	void setRotation(float angle);

    Weapon* getWeapon();
    virtual sf::Vector2f getTarget() const = 0;
	float getSpeed() const { return m_speed; }
    virtual void rotateTowardMouse(sf::RenderWindow&) {};

protected:
    
    World& m_world;
    float m_speed = 0.f;
	Character* m_target;
    std::unique_ptr<State> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    std::unique_ptr<VisionLight> m_visionLight;

    MoveInfo m_lastMoveInfo;
    std::unique_ptr <HealthBar> m_healthBar;
    float m_health = 100.f;
    float m_armor = 50.f;
    std::unique_ptr<ArmorBar> m_armorBar;
};


