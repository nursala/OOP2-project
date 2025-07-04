#pragma once

#include "CommandInc/Command.h"
#include "GameSessionData.h"
#include "WeaponInc/Weapon.h"
#include "ScreensInc/Market.h" 
#include "ResourseInc/SoundManager.h"

// -----------------------------
// SmartWeaponCommand - buy/equip a weapon in market screen
// -----------------------------
class SmartWeaponCommand : public Command {
public:
    SmartWeaponCommand(Constants::WeaponType weapon, Market& screen);
    void execute() override;

private:
    Constants::WeaponType m_weapon;
    Market& m_market;
};
