#pragma once

#include "GameObject/MovingObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Enemy : public MovingObject {
public:
	Enemy(b2World* world, const b2Vec2& position);
	~Enemy() override;
	void update(float deltaTime) override;
	void render(sf::RenderTarget& target);
	void move(float speed);

protected:
	sf::Vector2f m_playerPos;
	void setPlayerPosition(const sf::Vector2f& position) { m_playerPos = position; }
	virtual void createSensor(float radius) = 0;

private:
	void moveTowardsPlayer(const sf::Vector2f& playerPosition, const float& dt)
};