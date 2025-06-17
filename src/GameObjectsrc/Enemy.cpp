#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "LoadMap.h"
#include "GameObject/Player.h"
#include <iostream>
#include "StatesInc/ChasingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"

namespace {
	const bool reg = [] {
		Factory::instance().registerWithNavigation(TextureID::Enemy,
			[](b2World& world, const LoadMap& map, const Player& player) {
				int randomIQ = rand() % 10 + 1;
				std::cout << "Enemy IQ: " << randomIQ << std::endl;
				return std::make_unique<Enemy>(world, map, player, randomIQ);
			});
		return true;
		}();
}

Enemy::Enemy(b2World& world, const LoadMap& map, const Player& player, int iq)
	:Entity(world, TextureManager::instance().get(TextureID::Player), { 350,350 }, { 5, 5 }, 0.4f),
	m_playerRef(player)
{
    m_speed = 2.f;
	m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, iq);
    m_state = std::make_unique<ChasingState>();
    m_state->enter(*this);

	m_attackStrategy = std::make_unique<SimpleShootStrategy>();
}

Enemy::~Enemy() {
	if (m_body)
	{
		m_body->GetWorld()->DestroyBody(m_body);
	}
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
        float bulletDistance = std::sqrt(
            std::pow(currPos.x - m_bulletStartPos.x, 2) +
            std::pow(currPos.y - m_bulletStartPos.y, 2)
        );

        if (bulletDistance > 500.f) {
            m_bulletFired = false;
        }
    }

    sf::Vector2f pos = { m_body->GetPosition().x , m_body->GetPosition().y };
    pos *= SCALE;
    m_sprite.setPosition(pos);
    m_sprite.setTextureRect(m_animation.getUvRect());

    m_hitbox.setPosition(pos);
    m_hitbox.setRotation(m_sprite.getRotation());
    m_hitbox.setOrigin(m_hitbox.getSize().x / 2, m_hitbox.getSize().y / 2);
    m_hitbox.setTexture(m_sprite.getTexture());
    m_hitbox.setTextureRect(m_sprite.getTextureRect());
}

void Enemy::moveToPlayer(float deltaTime) {

    if (m_moveStrategy)
        m_lastMoveInfo = m_moveStrategy->move(*this, deltaTime);
}

bool Enemy::isPlayerVisible() const {
    RayCastClosest raycast;

    b2Vec2 start = b2Vec2(getPixels().x / SCALE, getPixels().y / SCALE);
    b2Vec2 end = b2Vec2(m_playerRef.getPixels().x / SCALE, m_playerRef.getPixels().y / SCALE);

    m_body->GetWorld()->RayCast(&raycast, start, end);

    return raycast.hit() && raycast.getBody() == m_playerRef.getBody();
}

float Enemy::distanceToPlayer() const {
    sf::Vector2f enemyPos = getPixels();
    sf::Vector2f playerPos = m_playerRef.getPixels();

    sf::Vector2f diff = playerPos - enemyPos;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

void Enemy::shootAtPlayer(float deltaTime) {
    m_body->SetLinearVelocity(b2Vec2_zero);
    if (m_attackStrategy)
        m_attackStrategy->attack(*this, deltaTime);
}

void Enemy::fireBullet(const sf::Vector2f& direction) {
    if (m_bulletFired) return;
    m_bulletFired = true;

    m_bullet.setSize({ 20.f, 6.f });
    m_bullet.setFillColor(sf::Color::Red);

    m_bulletStartPos = getPixels();
    m_bullet.setPosition(getPixels());

    m_bulletVelocity = direction * m_bulletSpeed;
}

void Enemy::render(sf::RenderWindow& window) {

	window.draw(m_hitbox);
	if (m_bulletFired) {
		window.draw(m_bullet);
	}
}

float Enemy::getShootingRange() const {
	return m_shootingRange;
}


