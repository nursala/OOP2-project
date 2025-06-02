#pragma once

#include "GameObject/Entity.h"

class Player : public Entity {
public:
    Player(b2World& world);
    void update(float deltaTime) override;

    void move(b2Vec2 speed);
    // Add player-specific methods here
private:

	sf::RectangleShape m_shape; // For rendering the player
};
