#include "ScreensInc/Market.h"
#include "GameSessionData.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/SmartWeaponCommand.h"
Market::Market()
{
	setBackGroundTexture(TextureID::MARKET);
    m_messageText.setFont(Controller::getInstance().getFont());
    m_messageText.setCharacterSize(24);
    m_messageText.setFillColor(sf::Color::Magenta);
    m_messageText.setPosition(500.f, 120.f); 
    m_messageText.setString("");
}

ScreenID Market::getScreenID() const
{
	return ScreenID::Market;
}

void Market::init()
{
    auto& basic = m_buttons.emplace(ButtonID::BasicGun, Button({ 120, 40 }, { 250, 365 }, "")).first->second;
    auto& shot = m_buttons.emplace(ButtonID::Rifle, Button({ 120, 40 }, { 850, 365 }, "")).first->second;
    auto& snipe = m_buttons.emplace(ButtonID::Shotgun, Button({ 120, 40 }, { 250, 620 }, "")).first->second;
    auto& laser = m_buttons.emplace(ButtonID::Sniper, Button({ 120, 40 }, { 850, 620 }, "")).first->second;

    m_weaponButtons = {
        {WeaponType::HandGun, &basic},
        {WeaponType::Shotgun,  &shot},
        {WeaponType::Sniper,   &snipe},
        {WeaponType::Rifle,    &laser}
    };

    basic.setCommand(std::make_unique<SmartWeaponCommand>(WeaponType::HandGun, *this));
    shot.setCommand(std::make_unique<SmartWeaponCommand>(WeaponType::Shotgun, *this));
    snipe.setCommand(std::make_unique<SmartWeaponCommand>(WeaponType::Sniper, *this));
    laser.setCommand(std::make_unique<SmartWeaponCommand>(WeaponType::Rifle, *this));

	auto& back = m_buttons.emplace(ButtonID::Back, Button({ 120, 40 }, { 100, 100 }, "Back")).first->second;
	back.setCommand(std::make_unique<PopScreenCommand>());
	updateWeaponButtonLabels();

}

void Market::updateWeaponButtonLabels() 
{
    auto& session = GameSessionData::instance();

    for (auto& [type, btn] : m_weaponButtons) 
    {
        if (!session.hasWeapon(type))
            btn->setText("Buy -" + std::to_string(Weapon::getPrice(type) )+ "$");
        else if (session.getSelectedWeapon() == type)
            btn->setText("Equipped");
        else
            btn->setText("Equip");
    }
}

void Market::render(sf::RenderWindow& window)
{
	Screen::render(window);
	//m_moneyText.setFont(Controller::getInstance().getFont());
	//m_moneyText.setCharacterSize(24);
	//m_moneyText.setFillColor(sf::Color::White);
	//m_moneyText.setPosition(10.f, 10.f);
	//m_moneyText.setString("Money: " + std::to_string(GameSessionData::instance().money));
	//window.draw(m_moneyText);
	window.draw(m_messageText);
}

void Market::setMessage(const std::string string)
{
	m_messageText.setString(string);
}