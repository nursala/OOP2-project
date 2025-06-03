#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"

namespace {
	const bool reg = [] {
		Factory::instance().registerType(TextureID::Player, [](b2World& world) {
			return std::make_unique<Player>(world);
			});
		return true;
		}();
}

Player::Player(b2World& world)
	: Entity(world, TextureManager::instance().get(TextureID::Player), { 100,100 }, { 5,5 }, 0.4)
{
}

void Player::update(float deltaTime)
{
	int row = 1;
	bool faceRight = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_body->SetLinearVelocity(b2Vec2(25.f, 0));
		row = 2;
		faceRight = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_body->SetLinearVelocity(b2Vec2(-25.f, 0));
		row = 2;
		faceRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_body->SetLinearVelocity(b2Vec2(0, -25.f));
		row = 2;
		faceRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_body->SetLinearVelocity(b2Vec2(0, 25.f));
		row = 2;
		faceRight = false;
	}
	else {
		m_body->SetLinearVelocity(b2Vec2(0.f, 0));
		row = 1;
	}

	sf::Vector2f pos = { m_body->GetPosition().x ,m_body->GetPosition().y };
	pos *= SCALE;
	m_sprite.setPosition(pos.x, pos.y);

	m_animation.update(row, 5, deltaTime, faceRight);
	m_sprite.setTextureRect(m_animation.getUvRect());
	m_hitbox.setPosition(pos.x, pos.y);
	m_hitbox.setRotation(m_sprite.getRotation());
	m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
	m_hitbox.setPosition(m_sprite.getPosition());
	m_hitbox.setTexture(m_sprite.getTexture());
	m_hitbox.setTextureRect(m_sprite.getTextureRect());
}
