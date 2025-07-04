#include "StatesInc/AttackingState.h"
#include "StatesInc/WalkingState.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManager.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"

void AttackingState::update(Character& character, float dt) 
{
	character.shoot(dt);
	character.move(dt);
	character.getAnimation().update(dt);
}

std::unique_ptr<State> AttackingState::handleInput(Character& character)
{
	if (character.getTarget())
	{
		return nullptr; // No target, return to walking state
	}
		
	auto& weaponData = Constants::WeaponDataMap.at(character.getWeapon()->getType());

	character.getAnimation().setAll(
		TextureManager::instance().get(weaponData.moveAnim.textureID),
		weaponData.moveAnim.frameSize,
		weaponData.moveAnim.speed
	);
	character.getSprite().setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));
	return std::make_unique<WalkingState>();
}