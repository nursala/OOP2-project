#pragma once

#include "GameObject/Character.h"
#include "GameObject/Player.h"
#include <SFML/Graphics.hpp>

class LoadMap;
class World;

class Enemy : public Character {
public:
    Enemy(World& world, b2Vec2& position ,const LoadMap& map, const Player& player, Constants::WeaponType& type);

    virtual ~Enemy() override = default;

    virtual Character* getClosestTarget();
    void takeDamage(int damage) override;
    void speedDown();
    void setSpeedDownTimer(float seconds); 
    void update(float deltaTime) override;

    void updateFootstepSound(float distanceToPlayer, float deltaTime);
    void setSpy(bool value);
    bool isSpy() const;
    void setSpyTimer(float seconds);
private:
    const Player& m_playerRef;
    bool m_isSpy = false;
    float m_spyTimer = 0.f;
    float m_footstepTimer = 0.f;
    float m_footstepInterval = 1.f;
    float m_speedDownTimer = 0.f; 
    float m_originalSpeed = 5.f;  
	float m_hideDelayTimer = 0.f; // Time for which the enemy is visible
};
