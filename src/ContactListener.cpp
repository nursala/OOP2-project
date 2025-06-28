#include "GameObject/ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"
#include <iostream>

ContactListener::ContactListener(World& world)
    : m_world(world) {
}

void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    if (!entityA || !entityB || !entityA->isVisible() || !entityB->isVisible())
        return;

    // === Player Collisions ===
    if (auto player = dynamic_cast<Player*>(entityA)) {
        if (auto bullet = dynamic_cast<Bullet*>(entityB)) {
            if (bullet->getOwner() != player) {
                // Prevent spy bullets from damaging player
                if (auto enemy = dynamic_cast<Enemy*>(bullet->getOwner()))
                    if (enemy->isSpy())
                        return;

                player->takeDamage(bullet->getDamage());
                bullet->setDestroyed(true);
            }
        }
        else if (auto gift = dynamic_cast<Gift*>(entityB)) {
            switch (gift->getType()) {
            case GiftType::ARMOR:
                player->addArmor();
                break;
            case GiftType::HEALTH:
                player->addHealth();
                break;
            case GiftType::SPEEDUP:
                player->addSpeed();
                break;
            case GiftType::ENEMYSPEEDDOWN:
                for (auto enemy : m_world.getEnemies())
                {
                    enemy->speedDown();
					enemy->setSpeedDownTimer(15.f);  // seconds of speed down
                }
                break;
            case GiftType::SPY:
                // Convert first non-spy enemy to spy
                for (auto enemy : m_world.getEnemies()) {
                    if (!enemy->isSpy()) {
                        enemy->setSpy(true);
                        enemy->setSpyTimer(20.f);  //seconds of spy behavior
                        break;
                    }
                }
                break;
			case GiftType::INCREASERANGE:
                player->increaseVisionTemporarily(100.f, 10.f); // example: +100 radius for 10 seconds
                break;
            default:
                throw std::runtime_error("Unknown GiftType");
            }
            gift->des();
        }
        else if (auto enemy = dynamic_cast<Enemy*>(entityB)) {
            // Optional: Player touches enemy
            // player->takeDamage(10);
        }
    }

    // === Enemy Collisions ===
    else if (auto enemy = dynamic_cast<Enemy*>(entityA)) {
        if (auto bullet = dynamic_cast<Bullet*>(entityB)) {
            if (bullet->getOwner() != enemy) {
                // Prevent player bullets from damaging spy
                if (enemy->isSpy() && dynamic_cast<Player*>(bullet->getOwner()))
                    return;
                
                enemy->takeDamage(bullet->getDamage());
                bullet->setDestroyed(true);
            }
        }
    }
}
