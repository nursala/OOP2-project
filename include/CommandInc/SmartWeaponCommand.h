
#pragma once
#include "CommandInc/Command.h"
#include "GameSessionData.h"
#include "WeponInc/Weapon.h"
#include "ScreensInc/Market.h" 

class SmartWeaponCommand : public Command {
public:
    SmartWeaponCommand(WeaponType weapon, Market& screen)
        : m_weapon(weapon), m_market(screen) {
    }

    void execute() override {
        auto& session = GameSessionData::instance();
        int price = Weapon::getPrice(m_weapon);

        if (!session.hasWeapon(m_weapon)) {
            if (session.money >= price) {
                session.money -= price;
                session.addWeapon(m_weapon);
                m_market.setMessage("Weapon purchased!");
            }
            else {
                m_market.setMessage("You don't have enough money!");
            }
        }
        else if (session.selectedWeapon != m_weapon) {
            session.selectedWeapon = m_weapon;
            m_market.setMessage("Weapon equipped!");
        }
        else {
            m_market.setMessage("Weapon already equipped.");
        }

		m_market.updateWeaponButtonLabels();

    }

private:
    WeaponType m_weapon;
    Market& m_market;
};