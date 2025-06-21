#include "GameObject/ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/ExtraHealthGift.h"
#include "GameObject/ExtraArmorGift.h"
#include "GameObject/SpeedUpGift.h"
#include "GameObject/EnemySpDwGift.h"
#include "GameObject/SpyGift.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact) {
	// Get the bodies involved in the contact
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
	// Get the user data associated with each body
    Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);



    // Example: Check if one is Player and one is Gift
    if (entityA && entityB) {
		/*std::cout << "EntityA: " << entityA->getPosition().x << ", " << entityA->getPosition().y << std::endl;
		std::cout << "EntityB: " << entityB->getPosition().x << ", " << entityB->getPosition().y << std::endl;*/
		//std::cout << "Contact between " << typeid(*entityA).name() << " and " << typeid(*entityB).name() << std::endl;
        if (!entityA->isVisible() || !entityB->isVisible())
            return;

        if (auto player = dynamic_cast<Player*>(entityA)) {
			//std::cout << "Player" << std::endl;
            if (auto gift = dynamic_cast<ExtraHealthGift*>(entityB)) {
                std::cout << "Extra Life" << std::endl;
                if (gift && gift->isVisible())
                {
                    std::cout << "Player collected a healthgift!" << std::endl;
                    gift->setVisible(false);
                   
                }
                player->addHealth();
            }
            else if (auto gift = dynamic_cast<ExtraArmorGift*>(entityB)) {
				std::cout << "Extra Armor" << std::endl;
                if (gift && gift->isVisible()) {
                    std::cout << "Player collided with a armor!" << std::endl;
					gift->setVisible(false);
                    player->addArmor();
                }
            }
			else if (auto gift = dynamic_cast<SpeedUpGift*>(entityB)) {
				std::cout << "Speed Up" << std::endl;
				if (gift && gift->isVisible()) {
					std::cout << "Player collected a speedupgift!" << std::endl;
					gift->setVisible(false);
				}
				player->addSpeed();
			}
			else if (auto gift = dynamic_cast<EnemySpDwGift*>(entityB)) {
				std::cout << "Enemy Speed Down" << std::endl;
				if (gift && gift->isVisible()) {
				    std::cout << "Player collided with a enemyspeedgift!" << std::endl;
					gift->setVisible(false);
					//enemy->speedDown();
				}
			}
			else if (auto gift = dynamic_cast<SpyGift*>(entityB)) {
				std::cout << "Spy" << std::endl;
				if (gift && gift->isVisible()) {
					std::cout << "Player collected a spy gift!" << std::endl;
					gift->setVisible(false);
					//player->setSpy(true); // Assuming Player has a method to set spy mode
				}
			}
			else if (auto enemy = dynamic_cast<Enemy*>(entityB)) {
				std::cout << "Player collided with an enemy!" << std::endl;
				player->takeDamage(10); // Example damage value
			}
        }
    }
}


//
//void ContactListener::BeginContact(b2Contact* contact) {
//    auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
//    auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
//
//    // Example: check types and handle collision
//    // if (objA && objB) { ...}
//	if (objA && objB) {
//		// Handle collision between objA and objB
//		// You can add your collision logic here
//		// For example, you might want to log the collision or trigger some game logic
//		// std::cout << "Collision detected between " << objA->getName() << " and " << objB->getName() << std::endl;
//	}
//
//}
//
//void ContactListener::EndContact(b2Contact* contact) {
//    // Similar to BeginContact
//	auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
//	auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
//	// Example: check types and handle end of collision
//	// if (objA && objB) { ...}
//	if (objA && objB) {
//		// Handle end of collision between objA and objB
//		// You can add your logic for when the collision ends
//		// For example, you might want to log the end of the collision or trigger some game logic
//		// std::cout << "Collision ended between " << objA->getName() << " and " << objB->getName() << std::endl;
//	}
//}