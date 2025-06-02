#include "GameObject/Enemy.h"
#include <SFML/Graphics/RenderTarget.hpp>

Enemy::Enemy(b2World* world, const b2Vec2& position)
	: MovingObject(world, position) {
	m_velocity = b2Vec2(5.0f, 5.0f);	
}


Enemy::~Enemy() {
	if (m_body)
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}
}

void Enemy::update(float deltaTime) {
	// Update the enemy's position based on its velocity
	b2Vec2 newPosition = getPosition() + m_velocity * deltaTime;
	setPosition(newPosition);
	// Update the sprite's position
	m_sprite.setPosition(newPosition.x, newPosition.y);

	// Additional update logic can be added here
}

//void Enemy::move(b2Vec2 speed) {

//}

void Enemy::render(sf::RenderTarget& target) {
	// Render the enemy sprite
	m_sprite.setPosition(getPosition().x, getPosition().y);
	target.draw(m_sprite);
}

void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, const float& dt)
{
    
        // Get current enemy position in SFML coordinates
        sf::Vector2f enemyPos(getPosition().x, getPosition().y);

        // Calculate direction vector toward the player
        sf::Vector2f direction = playerPosition - enemyPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0.0f) {
            direction.x /= length;
            direction.y /= length;

            // Set Box2D velocity toward the player
            b2Vec2 velocity(direction.x * m_velocity.x, direction.y * m_velocity.y);
            setVelocity(velocity);

            // Optionally, rotate the enemy to face the player
            float angle = std::atan2(direction.y, direction.x);
            m_body->SetTransform(m_body->GetPosition(), angle);
        }
        else {
            // Stop if already at the player's position
            setVelocity(b2Vec2_zero);
        }
}

