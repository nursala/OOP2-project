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
	m_state(std::make_unique<IdleStatePlayer>()),
	m_weapon(nullptr),
	m_healthBar(40.f, 5.f), // width and height
	m_maxHealth(200.f),
	m_health(200.f)
{
	m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
	if (m_state)
		m_state->enter(*this);
	m_weapon = std::make_unique<Weapon>(world);
	m_visable = true;
	m_healthBar.setMaxHealth(m_maxHealth);
	m_healthBar.setHealth(m_health);
	//m_healhBarBackground.setSize(sf::Vector2f(50.f, 5.f));
	//m_healhBarBackground.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent background
	//m_healhBarBackground.setPosition(m_hitbox.getPosition().x - 50.f, m_hitbox.getPosition().y - 50.f);
	//m_healhBarBackground.setOutlineColor(sf::Color::Black);
	//m_healhBarBackground.setOutlineThickness(1.f);
	//m_healthBar.setSize(sf::Vector2f(50.f, 5.f));
	//m_healthBar.setFillColor(sf::Color::Green);
	//// m_healthBar need to be changed when the player takes damage 
	//m_healthBar.setOrigin(m_healthBar.getSize().x / 2, m_healthBar.getSize().y / 2);
	//m_healthBar.setPosition( m_hitbox.getPosition().x - 50.f, m_hitbox.getPosition().y - 50.f);

}

void Player::setLight(std::shared_ptr<VisionLight>& visionLight)
{
	m_visionLight = visionLight;
}

void Player::setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight)
{
	m_weapon->setLight(weaponLight);
}

void Player::update(float deltaTime)
{
	MoveInfo info = { 1, true };
	if (m_moveStrategy)
		info = m_moveStrategy->move(*this, deltaTime);

	sf::Vector2f pos = { m_body->GetPosition().x ,m_body->GetPosition().y };
	pos *= SCALE;
	m_sprite.setPosition(pos.x, pos.y);

	m_sprite.setTextureRect(m_animation.getUvRect());

	m_weapon->update(pos, this->m_shape.getRotation());
	// hitbox updates
	m_hitbox.setPosition(pos.x, pos.y);
	m_hitbox.setRotation(m_sprite.getRotation());
	m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
	m_hitbox.setPosition(m_sprite.getPosition());
	m_hitbox.setTexture(m_sprite.getTexture());
	m_hitbox.setTextureRect(m_sprite.getTextureRect());

    m_healthBar.setPosition(sf::Vector2f(m_hitbox.getPosition().x, m_hitbox.getPosition().y - 20.f));
}

void Player::render(sf::RenderWindow& window)
{
	if (m_visable) {
		window.draw(m_hitbox);
		m_weapon->draw(window);
		m_healthBar.draw(window);
	}
}

void Player::takeDamage(float amount)
{
	m_health = std::max(0.f, m_health - amount);
	m_healthBar.setHealth(m_health);
}

void Player::setFacingRight(bool right) {
	if (m_lastMoveInfo.faceRight != right) {
		m_lastMoveInfo.faceRight = right;
		m_sprite.setScale(right ? 1.f : -1.f, 1.f);
	}
}
