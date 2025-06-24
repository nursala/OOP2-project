#pragma once
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "MoveStrategyAndInfoInc/MoveInfo.h"

class KeyboardMoveStrategy : public MoveStrategy {
public:
	MoveInfo move(Character& entity, float deltaTime) override;
};