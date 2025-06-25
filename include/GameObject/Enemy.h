#pragma once

#include "GameObject/Character.h"
#include "GameObject/Player.h"
#include <SFML/Graphics.hpp>

class LoadMap;
class World;

class Enemy : public Character {
public:
    Enemy(World& world, const LoadMap& map, const Player& player);
    ~Enemy() override;

    bool isPlayerVisible() const;
    float distanceToPlayer() const;
    void fireBullet(const sf::Vector2f& dir);
    void takeDamage(int damage) override;
    void speedDown();
    void setSpeedDownTimer(float seconds); 
    sf::Vector2f getTarget() const override;
    void update(float deltaTime) override;

    // Spy methods
    void setSpy(bool value);
    bool isSpy() const;
    void setSpyTimer(float seconds);

private:
    const Player& m_playerRef;
    bool m_isSpy = false;
    float m_spyTimer = 0.f;

    float m_speedDownTimer = 0.f; 
    float m_originalSpeed = 5.f;  
};
