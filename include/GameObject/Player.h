#pragma once

#include "GameObject/MovingObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player : public MovingObject {
public:
    Player(b2World* world, const b2Vec2& position);
    ~Player() override;

    void update(float deltaTime) override;
    void move(b2Vec2 speed);
    // Add player-specific methods here
private:
	sf::RectangleShape m_shape; // For rendering the player
};
