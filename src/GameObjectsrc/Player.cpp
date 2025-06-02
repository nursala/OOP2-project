#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player(b2World* world, const b2Vec2& position)
    : MovingObject(world, position) {
	m_velocity = b2Vec2(5.0f, 5.0f); // Set a default velocity for the player
	// Set the body type to dynamic for the player	
}

Player::~Player() {}

void Player::update(float deltaTime) {
	move(m_velocity);
}
// make the player move 

void Player::move(b2Vec2 speed) {
    b2Vec2 velc(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velc.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velc.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velc.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velc.x -= 1.0f;
    }

    velc.x *= m_velocity.x;
	velc.y *= m_velocity.y;
    setVelocity(velc);
}