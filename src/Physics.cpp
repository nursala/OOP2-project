#include "Physics.h"


// Initialize the Box2D world with no gravity
b2World Physics::world(b2Vec2(0.0f, 0.0f));
float Physics::elapsedTime = 0.0f;

//-----------------------------------------------
// Initialize the physics world
void Physics::init() {
    //world.SetContactListener(&contactListener);
}

//-----------------------------------------------
// Update the physics world by stepping through the simulation
void Physics::update(float deltaTime) {
    world.Step(deltaTime, 8, 3);

    elapsedTime += deltaTime;
    if (elapsedTime >= 0.6f) {
        //contactListener.update();
        elapsedTime = 0.0f; // Reset the timer
    }
}
