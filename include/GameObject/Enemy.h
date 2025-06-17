#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "GameObject/Entity.h"
#include "Factory.h"
#include "StatesInc/State.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "GameObject/Player.h"
#include "HealthBar.h"

class Enemy : public Entity {
public:
	Enemy(b2World& world);
	~Enemy() override;

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

	void moveToPlayer(float deltaTime);
	bool isPlayerVisible() const;
	float distanceToPlayer() const;
	void shootAtPlayer(float deltaTime);
	void fireBullet(const sf::Vector2f& dir);

	float getShootingRange() const;
	sf::Vector2f getPlayerPos() const { return m_playerRef.getPixels(); }

private:
	std::unique_ptr<State<Enemy>> m_state;

	std::unique_ptr<AttackStrategy> m_attackStrategy;

	const Player& m_playerRef;

	HealthBar m_healthBar;

	sf::RectangleShape m_bullet;
	sf::Vector2f m_bulletVelocity;
	sf::Vector2f m_bulletStartPos;
	bool m_bulletFired = false;
	float m_bulletSpeed = 400.f;
	float m_shootingRange = 250.f;

};
