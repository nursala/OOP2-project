#pragma once

#include "GameObject/Character.h"  // هذا لازم يكون أول شيء
#include "GameObject/Player.h"  // هذا لازم يكون أول شيء
#include <SFML/Graphics.hpp>       // لو بدك تستخدم sf::Vector2f مثلاً

// التصريحات فقط، طالما تستخدم مراجع أو مؤشرات
class LoadMap;
class World;

class Enemy : public Character<Enemy> {
public:
    Enemy(World& world, const LoadMap& map, const Player& player, int iq);
    ~Enemy() override;
    sf::Vector2f getPlayerPos() { return m_playerRef.getPosition(); };
    bool isPlayerVisible() const;
    float distanceToPlayer() const;
    void shootAtPlayer(float deltaTime);
    void fireBullet(const sf::Vector2f& dir);
    float getShootingRange() const;
    void moveToPlayer(float deltaTime);

private:
    const Player& m_playerRef;
};
