#include "ScreensInc/Market.h"
#include "GameSessionData.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/SmartWeaponCommand.h"
#include "WeaponInc/Weapon.h"

Market::Market()
{
	setBackGroundTexture(Constants::TextureID::MARKET);
	setSize();
	m_messageText.setCharacterSize(Constants::CHAR_SIZE);
	m_messageText.setFillColor(sf::Color::Magenta);
	m_messageText.setFont(Controller::getInstance().getFont());
	m_messageText.setString("");
	m_money.first.setTexture(TextureManager::instance().get(Constants::TextureID::COINSMARKET));
	m_money.first.setSize(sf::Vector2f(Constants::WINDOW_WIDTH * 0.08f, Constants::WINDOW_HEIGHT * 0.1f));
	m_money.first.setPosition(Constants::WINDOW_WIDTH * 0.75f, Constants::WINDOW_HEIGHT * 0.05f);
	m_money.second.setFont(Controller::getInstance().getFont());
	m_money.second.setCharacterSize(Constants::CHAR_SIZE);
	m_money.second.setFillColor(sf::Color::White);
	m_money.second.setPosition(m_money.first.getSize().x + m_money.first.getPosition().x + Constants::MARGIN,
		m_money.first.getPosition().y);
}

Constants::ScreenID Market::getScreenID() const
{
	return Constants::ScreenID::Market;
}

void Market::init()
{
	m_weaponButtonInfo.clear();
	m_buttonInfos.clear();

	m_weaponButtonInfo.emplace_back(Constants::WeaponType::HandGun, Constants::ButtonID::BasicGun,
		Constants::TextureID::BASICGUN,
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2, Constants::WINDOW_HEIGHT * 0.506),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09)
	);

	m_weaponButtonInfo.emplace_back(Constants::WeaponType::Shotgun, Constants::ButtonID::Shotgun,
		Constants::TextureID::SHOTGUN,
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.69, Constants::WINDOW_HEIGHT * 0.506),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09)
	);

	m_weaponButtonInfo.emplace_back(Constants::WeaponType::Sniper, Constants::ButtonID::Sniper,
		Constants::TextureID::SNIPER,
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2, Constants::WINDOW_HEIGHT * 0.861),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09)
	);
	m_weaponButtonInfo.emplace_back(Constants::WeaponType::Rifle, Constants::ButtonID::Rifle,
		Constants::TextureID::RIFLE,
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.69, Constants::WINDOW_HEIGHT * 0.861),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09)
	);

	m_buttonInfos.emplace_back(
		Constants::ButtonID::Back,
		"Back",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
		std::make_unique<PopScreenCommand>()
	);

	setShapes();
	setButtons();
	updateWeaponButtonLabels();
}

void Market::setShapes()
{
	for (const auto& info : m_weaponButtonInfo)
	{
		auto& btn = m_buttons.emplace(info.id, Button(info.size, info.position)).first->second;
		btn.setCommand(std::make_unique<SmartWeaponCommand>(info.type, *this));

		sf::RectangleShape shape(sf::Vector2f(Constants::WINDOW_WIDTH * 0.2, Constants::WINDOW_HEIGHT * 0.15));
		sf::Vector2f pos = { info.position.x  ,info.position.y - 2*info.size.y - Constants::MARGIN};
		shape.setTexture(TextureManager::instance().get(info.textureID));
		shape.setPosition(pos);
		m_weaponButtons.emplace(info.type, std::make_pair(shape, &btn));
	}
}

void Market::updateWeaponButtonLabels()
{
	auto& session = GameSessionData::instance();

	for (auto& [type, pair] : m_weaponButtons)
	{
		if (!session.hasWeapon(type))
			pair.second->setText("Buy -" + std::to_string(Constants::WeaponPrice[type]) + "$");
		else if (session.getSelectedWeapon() == type)
			pair.second->setText("Equipped");
		else
			pair.second->setText("Equip");
	}
}

void Market::render(sf::RenderWindow& window)
{
	Screen::render(window);
	for (auto& [type, pair] : m_weaponButtons)
	{
		window.draw(pair.first); 
	}
	//Screen::render(window);
	//m_moneyText.setFont(Controller::getInstance().getFont());
	//m_moneyText.setCharacterSize(24);
	//m_moneyText.setFillColor(sf::Color::White);
	//m_moneyText.setPosition(10.f, 10.f);
	//m_moneyText.setString("Money: " + std::to_string(GameSessionData::instance().money));
	//window.draw(m_moneyText);
	m_money.second.setString(std::to_string(GameSessionData::instance().getMoney()));
	window.draw(m_money.second);
	window.draw(m_money.first);
	window.draw(m_messageText);
}

void Market::setMessage(const std::string string)
{
	m_messageText.setString(string);
    sf::FloatRect bounds = m_messageText.getLocalBounds();

    m_messageText.setOrigin(bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f);

    m_messageText.setPosition(Constants::WINDOW_WIDTH /2 , Constants::WINDOW_HEIGHT * 0.2);  
}