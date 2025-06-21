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
    bool isPlayerVisible() const;
    float distanceToPlayer() const;
    sf::Vector2f getTarget() const;
private:
    const Player& m_playerRef;
};
