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
	m_money.first.setTexture(TextureManager::instance().get(Constants::TextureID::COINS));
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
	m_generalButtons.clear();

	m_weaponButtonInfo.emplace_back(Constants::ButtonID::BasicGun,
		"",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2, Constants::WINDOW_HEIGHT * 0.506),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09),
		std::make_unique<SmartWeaponCommand>(Constants::WeaponType::HandGun, *this),
		Constants::TextureID::BASICGUN,
		Constants::WeaponType::HandGun
	);

	m_weaponButtonInfo.emplace_back(Constants::ButtonID::Shotgun,
		"",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.69, Constants::WINDOW_HEIGHT * 0.506),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09),
		std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Shotgun, *this),
		Constants::TextureID::SHOTGUN,
		Constants::WeaponType::Shotgun
	);

	m_weaponButtonInfo.emplace_back(Constants::ButtonID::Sniper,
		"",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2, Constants::WINDOW_HEIGHT * 0.861),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09),
		std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Sniper, *this),
		Constants::TextureID::SNIPER,
		Constants::WeaponType::Sniper
	);

	m_weaponButtonInfo.emplace_back(Constants::ButtonID::Rifle,
		"",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.69, Constants::WINDOW_HEIGHT * 0.861),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.15, Constants::WINDOW_HEIGHT * 0.09),
		std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Rifle, *this),
		Constants::TextureID::RIFLE,
		Constants::WeaponType::Rifle
	);

	m_weaponButtonInfo.emplace_back(
		Constants::ButtonID::Back,
		"Back",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
		std::make_unique<PopScreenCommand>()
	);

	setButtons<Constants::WeaponType>(m_weaponButtonInfo);
	updateWeaponButtonLabels();
}

void Market::updateWeaponButtonLabels()
{
	auto& session = GameSessionData::instance();

	for (auto& type : m_weaponButtons)
	{
		if (!session.hasWeapon(type.first))
			type.second->setText("Buy -" + std::to_string(Constants::WeaponPrice[type.first]) + "$");
		else if (session.getSelectedWeapon() == type.first)
			type.second->setText("Equipped");
		else
			type.second->setText("Equip");
	}
}

void Market::render(sf::RenderWindow& window)
{
	Screen::render(window);
	for (auto& image : m_weaponImages)
	{
		window.draw(image);
	}

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

	m_messageText.setPosition(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT * 0.2);
}


void Market::handleExtraButtonInfo(Constants::ButtonID id)
{
	for (const auto& info : m_weaponButtonInfo)
	{
		if (info.id != id)
			continue;

		auto it = m_buttons.find(info.id);
		if (it == m_buttons.end())
			return;

		sf::RectangleShape shape({ Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.15f });
		shape.setTexture(TextureManager::instance().get(info.textureID.value()));
		sf::Vector2f pos = {
			info.position.x,
			info.position.y - 2 * info.size.y - Constants::MARGIN
		};
		shape.setPosition(pos);
		m_weaponImages.push_back(std::move(shape));

		Button& btn = it->second;
		m_weaponButtons.emplace(info.type.value(), &btn);
		return;
	}
}
