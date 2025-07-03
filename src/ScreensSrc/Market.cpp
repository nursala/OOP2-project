#include "ScreensInc/Market.h"
#include "GameSessionData.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/SmartWeaponCommand.h"
#include "WeaponInc/Weapon.h"
#include "ResourseInc/TextureManager.h"
#include "Controller.h"

//-------------------------------------
// Market constructor
Market::Market() {
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
    m_money.second.setPosition(
        m_money.first.getSize().x + m_money.first.getPosition().x + Constants::MARGIN,
        m_money.first.getPosition().y
    );
}

//-------------------------------------
// Get screen ID
Constants::ScreenID Market::getScreenID() const {
    return Constants::ScreenID::Market;
}

//-------------------------------------
// Initialize weapon buttons and back button
void Market::init() {
    m_generalButtons.clear();

    m_weaponButtonInfo.emplace_back(Constants::ButtonID::BasicGun, "",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.506f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.15f, Constants::WINDOW_HEIGHT * 0.09f),
        std::make_unique<SmartWeaponCommand>(Constants::WeaponType::HandGun, *this),
        Constants::TextureID::BASICGUN,
        Constants::WeaponType::HandGun);

    m_weaponButtonInfo.emplace_back(Constants::ButtonID::Shotgun, "",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.69f, Constants::WINDOW_HEIGHT * 0.506f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.15f, Constants::WINDOW_HEIGHT * 0.09f),
        std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Shotgun, *this),
        Constants::TextureID::SHOTGUN,
        Constants::WeaponType::Shotgun);

    m_weaponButtonInfo.emplace_back(Constants::ButtonID::Sniper, "",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.861f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.15f, Constants::WINDOW_HEIGHT * 0.09f),
        std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Sniper, *this),
        Constants::TextureID::SNIPER,
        Constants::WeaponType::Sniper);

    m_weaponButtonInfo.emplace_back(Constants::ButtonID::Rifle, "",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.69f, Constants::WINDOW_HEIGHT * 0.861f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.15f, Constants::WINDOW_HEIGHT * 0.09f),
        std::make_unique<SmartWeaponCommand>(Constants::WeaponType::Rifle, *this),
        Constants::TextureID::RIFLE,
        Constants::WeaponType::Rifle);

    m_weaponButtonInfo.emplace_back(Constants::ButtonID::Back, "Back",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
        std::make_unique<PopScreenCommand>());

    setButtons<Constants::WeaponType>(m_weaponButtonInfo);
    updateWeaponButtonLabels();
}

//-------------------------------------
// Update labels based on weapon state
void Market::updateWeaponButtonLabels() {
    auto& session = GameSessionData::instance();

    for (auto& [type, button] : m_weaponButtons) {
        if (!session.hasWeapon(type))
            button->setText("Buy -" + std::to_string(Constants::WeaponPrice[type]) + "$");
        else if (session.getSelectedWeapon() == type)
            button->setText("Equipped");
        else
            button->setText("Equip");
    }
}

//-------------------------------------
// Render the market screen
void Market::render(sf::RenderWindow& window)
{
    Screen::render(window);

    for (auto& image : m_weaponImages)
        window.draw(image);

    m_money.second.setString(std::to_string(GameSessionData::instance().getMoney()));
    window.draw(m_money.second);
    window.draw(m_money.first);
    window.draw(m_messageText);
}

//-------------------------------------
// Set the center message on the screen
void Market::setMessage(const std::string string) {
    m_messageText.setString(string);

    const sf::FloatRect bounds = m_messageText.getLocalBounds();
    m_messageText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_messageText.setPosition(Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT * 0.2f);
}

//-------------------------------------
// Handle additional info from weapon buttons
void Market::handleExtraButtonInfo(Constants::ButtonID id) {
    for (const auto& info : m_weaponButtonInfo) {
        if (info.id != id)
            continue;

        auto it = m_buttons.find(info.id);
        if (it == m_buttons.end())
            return;

        sf::RectangleShape shape({ Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.15f });
        shape.setTexture(TextureManager::instance().get(info.textureID.value()));
        shape.setPosition({
            info.position.x,
            info.position.y - 2 * info.size.y - Constants::MARGIN });

        m_weaponImages.push_back(std::move(shape));

        Button& btn = it->second;
        m_weaponButtons.emplace(info.type.value(), &btn);
        return;
    }
}
