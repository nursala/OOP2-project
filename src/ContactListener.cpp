#include "ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"
#include "ResourseInc/SoundManager.h"
#include <iostream>

ContactListener::ContactListener(World& world)
    : m_world(world) {
}

//---------------------------------------
// Called when two fixtures begin to touch
void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);

    // === Player Collisions ===
    if (auto player = dynamic_cast<Player*>(entityA)) {
        if (auto gift = dynamic_cast<Gift*>(entityB)) {
            switch (gift->getType()) {
            case Constants::GiftType::ARMOR:
                player->addArmor();
                SoundManager::instance().play(Constants::SoundID::SHIELDUPGRADE);
                break;
            case Constants::GiftType::HEALTH:
                player->addHealth();
                SoundManager::instance().play(Constants::SoundID::HEALTHUPGRADE);
                break;
            case Constants::GiftType::SPEEDUP:
                player->addSpeed();
                SoundManager::instance().play(Constants::SoundID::SPEEDUPGRADE);
                break;
            case Constants::GiftType::ENEMYSPEEDDOWN:
                for (auto enemy : m_world.getEnemies()) {
                    enemy->speedDown();
                    SoundManager::instance().play(Constants::SoundID::SPEEDDOWN);
                    enemy->setSpeedDownTimer(10.f);
                }
                break;
            case Constants::GiftType::SPY:
                for (auto enemy : m_world.getEnemies()) {
                    if (!enemy->isSpy()) {
                        enemy->setSpy(true);
                        SoundManager::instance().play(Constants::SoundID::SPY);
                        enemy->setSpyTimer(20.f);
                        break;
                    }
                }
                break;
            case Constants::GiftType::VISIONUP:
                player->increaseVisionTemporarily(100.f, 10.f);
                SoundManager::instance().play(Constants::SoundID::VISIONUPGRADE);
                break;
            default:
                throw std::runtime_error("Unknown Constants::GiftType");
            }
            gift->setDestroyed(true);
        }
        else if (auto bullet = dynamic_cast<Bullet*>(entityB)) {
            auto shooter = bullet->getOwnerShared().get();
            if (shooter == player)
                return;

            if (auto enemyShooter = dynamic_cast<Enemy*>(shooter)) {
                if (!enemyShooter->isSpy()) {
                    player->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
        }
    }

    // === Enemy Collisions ===
    else if (auto enemy = dynamic_cast<Enemy*>(entityA)) {
        if (auto bullet = dynamic_cast<Bullet*>(entityB)) {
            auto shooter = bullet->getOwnerShared().get();
            if (shooter == enemy)
                return;

            if (dynamic_cast<Player*>(shooter)) {
                if (!enemy->isSpy()) {
                    enemy->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
            else if (auto shooterEnemy = dynamic_cast<Enemy*>(shooter)) {
                if (shooterEnemy != enemy && shooterEnemy->isSpy()) {
                    enemy->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
        }
    }

    // === Symmetric Cases ===
    else if (auto player = dynamic_cast<Player*>(entityB)) {
        if (auto bullet = dynamic_cast<Bullet*>(entityA)) {
            auto shooter = bullet->getOwnerShared().get();
            if (shooter == player)
                return;

            if (auto enemyShooter = dynamic_cast<Enemy*>(shooter)) {
                if (!enemyShooter->isSpy()) {
                    player->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
        }
    }

    else if (auto enemy = dynamic_cast<Enemy*>(entityB)) {
        if (auto bullet = dynamic_cast<Bullet*>(entityA)) {
            auto shooter = bullet->getOwnerShared().get();
            if (shooter == enemy)
                return;

            if (dynamic_cast<Player*>(shooter)) {
                if (!enemy->isSpy()) {
                    enemy->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
            else if (auto shooterEnemy = dynamic_cast<Enemy*>(shooter)) {
                if (shooterEnemy != enemy && shooterEnemy->isSpy()) {
                    enemy->takeDamage(bullet->getDamage());
                    bullet->setDestroyed(true);
                }
            }
        }
    }
}