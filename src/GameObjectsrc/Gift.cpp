#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "WorldInc/World.h"
#include <iostream> 

Gift::Gift(World& world, const sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount)
	: Entity(world, texture, position, imageCount, 0.4f),
	m_world(world)
{
    // Set up Box2D body as static or kinematic, and set up sprite
    m_visable = true;
	std::cout << "Sprite: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
	std::cout << "Body: " << getPosition().x << ", " << getPosition().y << std::endl;
}

GiftType Gift::getType() const { return m_type; }

void Gift::update(float deltaTime)
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

void Gift::des()
{
	if (m_body) {
		//m_body->SetUserData(nullptr); // Clear user data before destruction
		// Destroy the Box2D body associated with this gift
		m_world.getWorld().DestroyBody(m_body);
		m_body = nullptr;
	}
	m_visable = false; // Hide the gift after destruction
	setDestroyed(true); // Mark the gift as destroyed
}
