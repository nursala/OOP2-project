#include "StatesInc/WalkingState.h"
#include "StatesInc/AttackingState.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "iostream"

std::unique_ptr<State> WalkingState::handleInput(Character& character)
{
	if (character.getTarget()) {
		auto& weaponData = Constants::WeaponDataMap.at(character.getWeapon()->getType());

		character.getAnimation().setAll(
			TextureManager::instance().get(weaponData.shootAnim.textureID),
			weaponData.shootAnim.frameSize,
			weaponData.shootAnim.speed
		);
		character.getSprite().setTexture(*TextureManager::instance().get(weaponData.shootAnim.textureID));
		return std::make_unique<AttackingState>();
	}
	return nullptr;
}

void WalkingState::update(Character& character, float dt) {
	character.move(dt);
	character.getAnimation().update(dt);
}