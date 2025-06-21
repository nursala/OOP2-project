#include "GameObject/ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
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
		//std::cout << typeid(*entityA).name() << " && " << typeid(*entityB).name() << std::endl;
        if (!entityA->isVisible() || !entityB->isVisible())
            return;
		//std::cout << "Visible" << std::endl;
        if (auto player = dynamic_cast<Player*>(entityA)) {
			if (auto gift = dynamic_cast<Gift*>(entityB)) {
				switch (gift->getType())
				{
				case GiftType::ARMOR:
					std::cout << "Armor" << std::endl;
					player->addArmor();
					break;
				case GiftType::HEALTH:
					std::cout << "Health" << std::endl;
					player->addHealth();
					break;
				case GiftType::ENEMYSPEEDDOWN:
					std::cout << "Speed Down" << std::endl;
					//enemy->speedDown(); // Assuming you have a method to slow down enemies
					break;
				case GiftType::SPEEDUP:
					std::cout << "Speed Up" << std::endl;
					player->addSpeed();
					break;
				case GiftType::SPY:
					std::cout << "Spy" << std::endl;
					//player->setSpy(true); // Assuming Player has a method to set spy mode
					break;
				default:
					std::runtime_error("Unknown GiftType collected!");
					break;
				}
				gift->des();
			}

   //         if (auto gift = dynamic_cast<ExtraHealthGift*>(entityB)) {
   //             std::cout << "Extra Life" << std::endl;
   //             if (gift && gift->isVisible())
   //             {
   //                 std::cout << "Player collected a healthgift!" << std::endl;
   //                 gift->des();
   //                
   //             }
   //             player->addHealth();
   //         }
   //         else if (auto gift = dynamic_cast<ExtraArmorGift*>(entityB)) {
			//	std::cout << "Extra Armor" << std::endl;
   //             if (gift && gift->isVisible()) {
   //                 std::cout << "Player collided with a armor!" << std::endl;
			//		gift->des();
   //                 player->addArmor();
   //             }
   //         }
			//else if (auto gift = dynamic_cast<SpeedUpGift*>(entityB)) {
			//	std::cout << "Speed Up" << std::endl;
			//	if (gift && gift->isVisible()) {
			//		std::cout << "Player collected a speedupgift!" << std::endl;
			//		gift->des();
			//	}
			//	player->addSpeed();
			//}
			//else if (auto gift = dynamic_cast<EnemySpDwGift*>(entityB)) {
			//	std::cout << "Enemy Speed Down" << std::endl;
			//	if (gift && gift->isVisible()) {
			//	    std::cout << "Player collided with a enemyspeedgift!" << std::endl;
			//		gift->des();
			//		//enemy->speedDown();
			//	}
			//}
			//else if (auto gift = dynamic_cast<SpyGift*>(entityB)) {
			//	std::cout << "Spy" << std::endl;
			//	if (gift && gift->isVisible()) {
			//		std::cout << "Player collected a spy gift!" << std::endl;
			//		gift->des();
			//		//player->setSpy(true); // Assuming Player has a method to set spy mode
			//	}
			//}
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