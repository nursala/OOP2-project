#include "StatesInc/AttackingState.h"
#include "StatesInc/WalkingState.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManger.h"
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
	return (character.getTarget()) ? nullptr : std::make_unique<WalkingState>();
}