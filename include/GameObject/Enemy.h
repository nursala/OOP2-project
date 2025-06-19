#pragma once

#include "GameObject/Character.h" 
#include "GameObject/Player.h"  
#include <SFML/Graphics.hpp>     

class LoadMap;
class World;

class Enemy : public Character<Enemy> {
public:
    Enemy(World& world, const LoadMap& map, const Player& player, int iq);
    ~Enemy() override;
    sf::Vector2f getPlayerPos() { return m_playerRef.getPosition(); };
    bool isPlayerVisible() const;
    float distanceToPlayer() const;
    void fireBullet(const sf::Vector2f& dir);
    float getShootingRange() const;
private:
    const Player& m_playerRef;
};
