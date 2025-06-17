#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include <cmath>
#include "GameObject/Enemy.h"

void SimpleShootStrategy::attack(Enemy& enemy, float deltaTime) {
    sf::Vector2f dir = enemy.getPlayerPos() - enemy.getPixels();
    float len = std::hypot(dir.x, dir.y);

    if (len == 0.f)
        return;

    sf::Vector2f unitDir = dir / len;
    enemy.fireBullet(unitDir);
}
