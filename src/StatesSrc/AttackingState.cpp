#include "StatesInc/AttackingState.h"
#include "StatesInc/WalkingState.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManger.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"

void AttackingState::update(Character& character, float dt) 
{
	auto* weapon = character.getWeapon();

	character.shoot(dt);
	character.move(dt);

	auto& weaponData = Constants::WeaponDataMap.at(weapon->getType());

	character.getAnimation().setAll(
		TextureManager::instance().get(weaponData.shootAnim.textureID),
		weaponData.shootAnim.frameSize,
		weaponData.shootAnim.speed
	);
	character.getSprite().setTexture(*TextureManager::instance().get(weaponData.shootAnim.textureID));
	character.getAnimation().update(dt);
}

std::unique_ptr<State> AttackingState::handleInput(Character& character)
{
	return (character.getTarget()) ? nullptr : std::make_unique<WalkingState>();
}