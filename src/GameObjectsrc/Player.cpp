#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"

namespace {
	const bool reg = [] {
		Factory::instance().registerType(TextureID::Player, [](b2World& world) {
			return std::make_unique<Player>(world);
			});
		return true;
		}();
}

Player::Player(b2World& world)
	: Entity(world, TextureManager::instance().get(TextureID::Player), { 100,100 }, { 5,5 }, 0.4),
	m_moveStrategy(std::make_unique<KeyboardMoveStrategy>())
{
	m_visable = true;
}

void Player::setMoveStrategy(std::unique_ptr<MoveStrategy> strategy) {
	m_moveStrategy = std::move(strategy);
}

void Player::update(float deltaTime)
{
    MoveInfo info = { 1, true };
    if (m_moveStrategy)
        info = m_moveStrategy->move(*this, deltaTime);

    sf::Vector2f pos = { m_body->GetPosition().x ,m_body->GetPosition().y };
    pos *= SCALE;
    m_sprite.setPosition(pos.x, pos.y);

    m_animation.update(info.row, 5, deltaTime, info.faceRight);
    m_sprite.setTextureRect(m_animation.getUvRect());

    // hitbox updates
    m_hitbox.setPosition(pos.x, pos.y);
    m_hitbox.setRotation(m_sprite.getRotation());
    m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
    m_hitbox.setPosition(m_sprite.getPosition());
    m_hitbox.setTexture(m_sprite.getTexture());
    m_hitbox.setTextureRect(m_sprite.getTextureRect());
}

