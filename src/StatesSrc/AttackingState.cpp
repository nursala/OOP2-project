#include "StatesInc/AttackingState.h"
#include "StatesInc/WalkingState.h"

void AttackingState::update(Character& character, float dt) {
	character.shoot(dt);
	character.move(dt);
	const MoveInfo& info = character.getLastMoveInfo();
	character.getAnimation().update(info.row, dt);
}

std::unique_ptr<State> AttackingState::handleInput(Character& character)
{
	if (character.getTarget()) {
		return nullptr;
	}
	return std::make_unique<WalkingState>();
}