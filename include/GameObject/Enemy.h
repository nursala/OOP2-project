#pragma once

#include "GameObject/Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Enemy : public Entity {
public:
	Enemy(b2World& world);
	~Enemy() override;
	void update(float deltaTime) override;
protected:
	sf::Vector2f m_playerPos;
	void setPlayerPosition(const sf::Vector2f& position) { m_playerPos = position; }
	const sf::Vector2f getDirection() const;
private:
	sf::Vector2f m_direction;
	sf::RectangleShape m_shape;
};
