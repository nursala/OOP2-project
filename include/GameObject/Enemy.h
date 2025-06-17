#pragma once

#include "GameObject/Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Factory.h"
#include "StatesInc/State.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "GameObject/Player.h"
#include "LoadMap.h"

class Enemy : public Entity {
public:
	Enemy(b2World& world, const LoadMap& map, const Player& player, int iq);
	~Enemy() override;
	void update(float deltaTime) override;
	void moveToPlayer(float deltaTime);
	bool isPlayerVisible() const;
	float distanceToPlayer() const;
	void shootAtPlayer(float deltaTime);
	void fireBullet(const sf::Vector2f& dir);
	virtual void render(sf::RenderWindow& window);
	float getShootingRange() const;
	float getSpeed() const;
	sf::Vector2f getPlayerPos() const { return m_playerRef.getPixels(); }
private:
	sf::Vector2f m_direction;
	sf::RectangleShape m_shape;

	sf::RectangleShape m_bullet;
	sf::Vector2f m_bulletVelocity;
	sf::Vector2f m_bulletStartPos;

	std::unique_ptr<State<Enemy>> m_state;
	std::unique_ptr<AttackStrategy> m_attackStrategy;
	const Player& m_playerRef;

	bool m_bulletFired = false;
	float m_bulletSpeed = 400.f;
	float m_shootingRange = 250.f;
};
