// Character.h

#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"
#include "ArmorBar.h"
#include <box2d/b2_fixture.h>
#include <unordered_set>

class World;
class Weapon;
class RenderLayers;
class VisionLight;

class Character : public Entity, public std::enable_shared_from_this<Character>
{
public:
    Character(World& , const sf::Texture* , sf::Vector2f , sf::Vector2u , float );
   
	virtual ~Character() override = default; 

    virtual void update(float );
    void render(sf::RenderWindow& ) override;
    void render(RenderLayers& );
    const MoveInfo& getLastMoveInfo();
    virtual b2BodyType getBodyType() const override;
    void move(float );

    virtual void takeDamage(int ) = 0;
    virtual void shoot(float );

    float getShootingRange() const;
    void setShootingRange(float );
	void setRotation(float );
	void updateTargets();
    void updateTargets(sf::RenderWindow& window);

	void setTarget(std::shared_ptr<Character> target) {
		m_target = target;
	}

	std::shared_ptr<Character> getTarget() const {
		return m_target.lock(); // Convert weak pointer to shared pointer
	}

    virtual Character* getClosestTarget() = 0;

    Weapon* getWeapon();
	float getSpeed() const { return m_speed; }
    virtual void rotateTowardMouse(sf::RenderWindow&) {};

protected:
    
    World& m_world;

    float m_speed = 0.f;

    std::unique_ptr<State> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    std::unique_ptr<VisionLight> m_visionLight;
    std::unique_ptr <HealthBar> m_healthBar;
    std::unique_ptr<ArmorBar> m_armorBar;


	std::weak_ptr<Character> m_target; // Weak pointer to avoid circular references

    std::shared_ptr<VisionLight> m_visionLight;
    MoveInfo m_lastMoveInfo;


    float m_health = 100.f;
    float m_armor = 50.f;
	float m_visableTime = 0.1f; // Time for which the character is visible

    std::unordered_set<b2Fixture*> m_hitFixtures;
};


