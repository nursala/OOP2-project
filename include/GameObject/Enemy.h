#pragma once

#include "GameObject/Character.h" 
#include "GameObject/Player.h"  
#include <SFML/Graphics.hpp>     

class LoadMap;
class World;

class Enemy : public Character {
public:
    Enemy(World& world, const LoadMap& map, const Player& player, int iq);
    ~Enemy() override;
    sf::Vector2f getPlayerPos() { return m_playerRef.getPosition(); };
    bool isPlayerVisible() const;
    float distanceToPlayer() const;
    void fireBullet(const sf::Vector2f& dir);
    void takeDamage(int damage) override;
    float getShootingRange() const;
    void speedDown();
private:
    const Player& m_playerRef;
};
