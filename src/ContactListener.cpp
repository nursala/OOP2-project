#include "ContactListener.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"

//---------------------------------------------
// Constructor
//---------------------------------------------
ContactListener::ContactListener(World& world)
    : m_world(world) {
}

//---------------------------------------------
// BeginContact: Core dispatch logic
//---------------------------------------------
void ContactListener::BeginContact(b2Contact* contact) {
    Entity* entityA = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Entity* entityB = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (!entityA || !entityB) return;

    // First dispatch: A handles B
    entityA->onCollide(*entityB);

    // Second dispatch: B handles A
    entityB->onCollide(*entityA);
}
