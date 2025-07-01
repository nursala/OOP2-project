#pragma once
#include "MoveStrategyAndInfoInc/MoveStrategy.h"

class KeyboardMoveStrategy : public MoveStrategy {
public:
	void move(Character& entity, float deltaTime) override;
};