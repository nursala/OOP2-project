#include "CommandInc/SmartWeaponCommand.h"
#include "GameSessionData.h"

SmartWeaponCommand::SmartWeaponCommand(Constants::WeaponType weapon, Market& screen)
    : m_weapon(weapon), m_market(screen) {
}

void SmartWeaponCommand::execute() {
    auto& session = GameSessionData::instance();
    int price = Constants::WeaponPrice[m_weapon];

    if (!session.hasWeapon(m_weapon)) {
        if (session.getMoney() >= price) {
            session.setMoney(session.getMoney() - price);
            session.addWeapon(m_weapon);
            m_market.setMessage("Weapon purchased!");
            SoundManager::instance().play(Constants::SoundID::COINS);
        }
        else {
            m_market.setMessage("You don't have enough money!");
        }
    }
    else if (session.getSelectedWeapon() != m_weapon) {
        session.setSelectedWeapon(m_weapon);
        m_market.setMessage("Weapon equipped!");
    }
    else {
        m_market.setMessage("Weapon already equipped.");
    }

    m_market.updateWeaponButtonLabels();
}
