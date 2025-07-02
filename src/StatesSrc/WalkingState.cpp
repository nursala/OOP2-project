#include "StatesInc/WalkingState.h"
#include "StatesInc/AttackingState.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
std::unique_ptr<State> WalkingState::handleInput(Character& character)
{
	if (auto player = dynamic_cast<Player*>(&character)) {
		if (character.getTarget()) {
			return std::make_unique<AttackingState>();
		}
		return nullptr;
	}

	else if (auto enemy = dynamic_cast<Enemy*>(&character)) {
		return std::make_unique<AttackingState>();
	}

	return nullptr;
}

void WalkingState::update(Character& character, float dt) {
	character.move(dt);

	auto& weaponData = Constants::WeaponDataMap.at(character.getWeapon()->getType());

	character.getAnimation().setAll(
		TextureManager::instance().get(weaponData.moveAnim.textureID),
		weaponData.moveAnim.frameSize,
		weaponData.moveAnim.speed
	);
	character.getSprite().setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));
	character.getAnimation().update(dt);
}