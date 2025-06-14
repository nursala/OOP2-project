#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"

namespace {
	const bool reg = [] {
		Factory::instance().registerType(TextureID::Enemy, [](b2World& world) {
			return std::make_unique<Enemy>(world);
			});
		return true;
		}();
}

Enemy::Enemy(b2World& world)  
   : Entity(world, TextureManager::instance().get(TextureID::Player), { 350,350 }, { 5, 5 }, 0.4f) ,
	m_healthBar(40.f, 5.f), // width and height
	m_maxHealth(100.f),
	m_health(100.f)
{  
   //m_moveStrategy = std::make_unique<IQChaseStrategy>(Player(world), 1); 
   m_sprite.setColor(sf::Color::Red);
   m_visable = true;
}

Enemy::~Enemy() {
	if (m_body)
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}
}

void Enemy::update(float deltaTime) {
	if (m_moveStrategy)
		m_lastMoveInfo = m_moveStrategy->move(*this, deltaTime);

	/*if (m_state) {
		auto newState = m_state->handleInput(*this);
		if (newState) {
			m_state = std::move(newState);
			m_state->enter(*this);
		}
		m_state->update(*this, deltaTime);
	}*/

	sf::Vector2f pos = { m_body->GetPosition().x , m_body->GetPosition().y };
	pos *= SCALE;
	m_sprite.setPosition(pos.x, pos.y);

	m_sprite.setTextureRect(m_animation.getUvRect());
	m_sprite.setColor(sf::Color::Red);

	m_hitbox.setPosition(pos);
	m_hitbox.setRotation(m_sprite.getRotation());
	m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
	m_hitbox.setPosition(m_sprite.getPosition());
	m_hitbox.setTexture(m_sprite.getTexture());
	m_hitbox.setTextureRect(m_sprite.getTextureRect());
}


//void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, const float& dt)
//{
//        // Get current enemy position in SFML coordinates
//        sf::Vector2f enemyPos(getPosition().x, getPosition().y);
//
//        // Calculate direction vector toward the player
//        sf::Vector2f direction = playerPosition - enemyPos;
//        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//        if (length > 0.0f) {
//            direction.x /= length;
//            direction.y /= length;
//
//            // Set Box2D velocity toward the player
//            b2Vec2 velocity(direction.x * m_velocity.x, direction.y * m_velocity.y);
//			setVelocity(velocity);
//
//            // Optionally, rotate the enemy to face the player
//            float angle = std::atan2(direction.y, direction.x);
//            m_body->SetTransform(m_body->GetPosition(), angle);
//        }
//        else {
//            // Stop if already at the player's position
//            setVelocity(b2Vec2_zero);
//        }
//}