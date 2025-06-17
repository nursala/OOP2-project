#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "LoadMap.h"
#include "GameObject/Player.h"
#include <iostream>
#include "StatesInc/ChasingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"

Enemy::Enemy(b2World& world, const LoadMap& map, const Player& player, int iq)
	: Entity(world, TextureManager::instance().get(TextureID::Player), { 350, 350 }, { 5, 5 }, 0.4f),
	m_playerRef(player),
	m_healthBar(40.f, 5.f, 100)
{
	m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, iq);
	m_state = std::make_unique<ChasingState>();
	m_state->enter(*this);

	m_attackStrategy = std::make_unique<SimpleShootStrategy>();

	m_speed = 2.f;
	
}

Enemy::~Enemy() {
	if (m_body)
		m_body->GetWorld()->DestroyBody(m_body);
}

void Enemy::update(float deltaTime) {
	if (m_state) {
		auto newState = m_state->handleInput(*this);
		if (newState) {
			m_state = std::move(newState);
			m_state->enter(*this);
		}
		m_state->update(*this, deltaTime);
	}

	if (m_bulletFired) {
		m_bullet.move(m_bulletVelocity * deltaTime);

		sf::Vector2f currPos = m_bullet.getPosition();
		float bulletDistance = std::hypot(
			currPos.x - m_bulletStartPos.x,
			currPos.y - m_bulletStartPos.y
		);

		if (bulletDistance > 500.f) {
			m_bulletFired = false;
		}
	}

	m_sprite.setPosition(getPixels());
	m_sprite.setTextureRect(m_animation.getUvRect());
}

void Enemy::moveToPlayer(float deltaTime) {
	if (m_moveStrategy)
		m_lastMoveInfo = m_moveStrategy->move(*this, deltaTime);
}

bool Enemy::isPlayerVisible() const {
	RayCastClosest raycast;

	b2Vec2 start = { getPixels().x / SCALE, getPixels().y / SCALE };
	b2Vec2 end = { m_playerRef.getPixels().x / SCALE, m_playerRef.getPixels().y / SCALE };

	m_body->GetWorld()->RayCast(&raycast, start, end);

	return raycast.hit() && raycast.getBody() == m_playerRef.getBody();
}

float Enemy::distanceToPlayer() const {
	sf::Vector2f enemyPos = getPixels();
	sf::Vector2f playerPos = m_playerRef.getPixels();

	sf::Vector2f diff = playerPos - enemyPos;
	return std::hypot(diff.x, diff.y);
}

void Enemy::shootAtPlayer(float deltaTime) {
	m_body->SetLinearVelocity(b2Vec2_zero);
	if (m_attackStrategy)
		m_attackStrategy->attack(*this, deltaTime);
}

void Enemy::fireBullet(const sf::Vector2f& direction) {
	if (m_bulletFired)
		return;

	m_bulletFired = true;

	m_bullet.setSize({ 20.f, 6.f });
	m_bullet.setFillColor(sf::Color::Red);

	m_bulletStartPos = getPixels();
	m_bullet.setPosition(m_bulletStartPos);

	m_bulletVelocity = direction * m_bulletSpeed;
}

void Enemy::render(sf::RenderWindow& window) {
	window.draw(m_sprite);

	if (m_bulletFired) {
		window.draw(m_bullet);
	}
}

float Enemy::getShootingRange() const {
	return m_shootingRange;
}
