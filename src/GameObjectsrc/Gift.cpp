#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "WorldInc/World.h"
#include <iostream> 

Gift::Gift(World& world, const sf::Texture* texture)
	: Entity(world, texture,  {100, 100}, {1, 1}, 0.4f),
	m_world(world)
{
    // Set up Box2D body as static or kinematic, and set up sprite
    m_visable = true;
	m_bodyRadius = 0.6f; // Set a default radius for the gift
	//m_sprite.setScale(m_sprite.getScale().x * 0.5f, m_sprite.getScale().y * 0.5f);
}

GiftType Gift::getType() const { return m_type; }

void Gift::update(float)
{
	if (m_body) {
		b2Vec2 pos = m_body->GetPosition();
		m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	}
}

void Gift::render(sf::RenderWindow& window)
{
	if (isVisible())
		window.draw(m_sprite);
}

void Gift::customizeFixtureDef(b2FixtureDef& fixtureDef)
{
	fixtureDef.isSensor = true; 
}

void Gift::des()
{
	//if (m_body) {
	//	//m_body->SetUserData(nullptr); // Clear user data before destruction
	//	// Destroy the Box2D body associated with this gift
	//	//m_world.getWorld().DestroyBody(m_body);
	//	m_body = nullptr;
	//}
	m_visable = false; // Hide the gift after destruction
	setDestroyed(true); // Mark the gift as destroyed
}
