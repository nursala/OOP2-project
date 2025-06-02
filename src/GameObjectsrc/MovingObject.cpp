#include "GameObject/MovingObject.h"

MovingObject::MovingObject(b2World* world, const b2Vec2& position, const b2Vec2& velocity)
    : GameObject(world, position)
{
    if (m_body) {
        m_body->SetType(b2_dynamicBody);
        m_body->SetLinearVelocity(velocity);
    }
}

MovingObject::~MovingObject() {}

b2Vec2 MovingObject::getVelocity() const {
    return m_body ? m_body->GetLinearVelocity() : b2Vec2_zero;
}

void MovingObject::setVelocity(const b2Vec2& velocity) {
    if (m_body) m_body->SetLinearVelocity(velocity);
}

void MovingObject::update(float /*deltaTime*/) {
	if (m_body) {
		// Update position based on the body's current velocity
		b2Vec2 position = m_body->GetPosition();
		// You can add custom logic here if needed
		// For example, you might want to log the position or perform other updates
	}
}
