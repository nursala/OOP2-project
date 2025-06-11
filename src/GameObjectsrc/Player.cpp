#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include <iostream>

namespace {
	const bool reg = [] {
		Factory::instance().registerType(TextureID::Player, [](b2World& world) {
			return std::make_unique<Player>(world);
			});
		return true;
		}();
}

Player::Player(b2World& world)
	: Entity(world, TextureManager::instance().get(TextureID::Player), { 100, 100 }, { 5, 5 }, 0.4),
	m_state(std::make_unique<IdleStatePlayer>())
{
	m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
	if (m_state)
		m_state->enter(*this);
}

void Player::update(float deltaTime) {
	if (m_moveStrategy)
		m_lastMoveInfo = m_moveStrategy->move(*this, deltaTime);

	if (m_state) {
		auto newState = m_state->handleInput(*this);
		if (newState) {
			m_state = std::move(newState);
			m_state->enter(*this);
		}
		m_state->update(*this, deltaTime);
	}

	sf::Vector2f pos = { m_body->GetPosition().x , m_body->GetPosition().y };
	pos *= SCALE;
	m_sprite.setPosition(pos.x, pos.y);

	m_sprite.setTextureRect(m_animation.getUvRect());

	m_hitbox.setPosition(pos);
	m_hitbox.setRotation(m_sprite.getRotation());
	m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
	m_hitbox.setTexture(m_sprite.getTexture());
	m_hitbox.setTextureRect(m_sprite.getTextureRect());
}

void Player::setFacingRight(bool right) {
	if (m_lastMoveInfo.faceRight != right) {
		m_lastMoveInfo.faceRight = right;
		m_sprite.setScale(right ? 1.f : -1.f, 1.f);
	}
}
