#include "StatesInc/AttackingStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"

std::unique_ptr<State> AttackingStatePlayer::handleInput(Character& character) {
	Player& player = static_cast<Player&>(character);

	if (!player.EnemyIsVisible().first || player.EnemyIsVisible().second > player.getShootingRange()) {
		return std::make_unique<WalkingStatePlayer>();
	}

	return nullptr;
}

