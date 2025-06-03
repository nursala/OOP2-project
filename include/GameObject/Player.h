#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
class Player : public Entity {
public:
    Player(b2World& world);
    void update(float deltaTime) override;

    void setMoveStrategy(std::unique_ptr<MoveStrategy> strategy);
private:

    std::unique_ptr<MoveStrategy> m_moveStrategy;
	sf::RectangleShape m_shape; // For rendering the player
};
