#include "GameObject/ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
    Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);


    //if (entityA) std::cout << "entityA: " << typeid(*entityA).name() << std::endl;
    //if (entityB) std::cout << "entityB: " << typeid(*entityB).name() << std::endl;

    // Example: Check if one is Player and one is Gift
    if (entityA && entityB) {
        if (!entityA->isVisible() || !entityB->isVisible())
            return;

        if (auto player = dynamic_cast<Player*>(entityA)) {
            //if (auto gift = dynamic_cast<Gift*>(entityB)) {
            //    if (gift && gift->isVisible())
            //    {
            //        std::cout << "Player collected a gift!" << std::endl;
            //        gift->setVisible(false);
            //    }
            //    // gift->apply(*player);
            //}
            //else if (auto enemy = dynamic_cast<Enemy*>(entityB)) {
            //    if (enemy && enemy->isVisible()) {
            //        std::cout << "Player collided with an enemy!" << std::endl;
            //    }
            //}
        }



        //else if (auto enemy = dynamic_cast<Enemy*>(entityA)) {
        //	if (auto player = dynamic_cast<Player*>(entityB)) {
        //		if (player && player->isVisible()) {
        //			std::cout << "Enemy collided with a player!" << std::endl;
        //			//enemy->attack(*player); // Example attack
        //		}
        //	}
        //}
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