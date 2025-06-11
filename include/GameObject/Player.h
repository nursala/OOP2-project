#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"

class Player : public Entity {
public:
    Player(b2World& world);
    void update(float deltaTime) override;
    void setFacingRight(bool isFaceRight);
private:
	std::unique_ptr<State<Player>> m_state; // Current state of the player
	sf::RectangleShape m_shape; // For rendering the player
	MoveInfo m_lastMoveInfo; // Last move info for the player
};
