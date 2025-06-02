#include "ContactListener.h"
#include "GameObject/GameObject.h"

void ContactListener::BeginContact(b2Contact* contact) {
    auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    // Example: check types and handle collision
    // if (objA && objB) { ...}
	if (objA && objB) {
		// Handle collision between objA and objB
		// You can add your collision logic here
		// For example, you might want to log the collision or trigger some game logic
		// std::cout << "Collision detected between " << objA->getName() << " and " << objB->getName() << std::endl;
	}

}

void ContactListener::EndContact(b2Contact* contact) {
    // Similar to BeginContact
	auto* objA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	auto* objB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	// Example: check types and handle end of collision
	// if (objA && objB) { ...}
	if (objA && objB) {
		// Handle end of collision between objA and objB
		// You can add your logic for when the collision ends
		// For example, you might want to log the end of the collision or trigger some game logic
		// std::cout << "Collision ended between " << objA->getName() << " and " << objB->getName() << std::endl;
	}
}