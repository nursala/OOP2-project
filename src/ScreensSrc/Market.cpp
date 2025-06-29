#include "ScreensInc/Market.h"
#include "GameSessionData.h"
#include "CommandInc/SmartWeaponCommand.h"
#include "CommandInc/PopScreenCommand.h"
#include "WeaponInc/Weapon.h"
#include "ResourseInc/TextureManager.h"
#include "Controller.h"

Market::Market() {
    setBackGroundTexture(Constants::TextureID::MARKET);
    setSize();

    m_messageText.setFont(Controller::getInstance().getFont());
    m_messageText.setCharacterSize(Constants::CHAR_SIZE);
    m_messageText.setFillColor(sf::Color::Magenta);
    m_messageText.setString("");
}

Constants::ScreenID Market::getScreenID() const {
    return Constants::ScreenID::Market;
}

void Market::init() {
    m_weaponButtonInfo.clear();

    m_weaponButtonInfo.emplace_back(
        Constants::ButtonID::BasicGun,
        "",
        sf::Vector2f(200, 300),
        sf::Vector2f(150, 90),
        std::make_unique<SmartWeaponCommand>(Constants::WeaponType::HandGun, *this),
        Constants::TextureID::BASICGUN,
        Constants::WeaponType::HandGun
    );

    m_weaponButtonInfo.emplace_back(
        Constants::ButtonID::Back,
        "Back",
        sf::Vector2f(100, 50),
        sf::Vector2f(100, 50),
        std::make_unique<PopScreenCommand>()
    );

    setButtons<Constants::WeaponType>(m_weaponButtonInfo);
    updateWeaponButtonLabels();
}

void Market::render(sf::RenderWindow& window) {
    Screen::render(window);

    for (const auto& shape : m_weaponImages)
        window.draw(shape);

    m_money.second.setString(std::to_string(GameSessionData::instance().getMoney()));
    window.draw(m_money.second);
    window.draw(m_money.first);
    window.draw(m_messageText);
}

void Market::setMessage(const std::string string) {
    m_messageText.setString(string);
    auto bounds = m_messageText.getLocalBounds();
    m_messageText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_messageText.setPosition(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT * 0.2);
}

void Market::updateWeaponButtonLabels() {
    for (auto& pair : m_weaponButtons) {
        if (!GameSessionData::instance().hasWeapon(pair.first))
            pair.second->setText("Buy");
        else
            pair.second->setText("Equip");
    }
}

template <>
void Screen::handleExtraButtonInfo<Constants::WeaponType>(
    const Constants::GenericButton<Constants::WeaponType>& info)
{
    if (!info.type.has_value() || !info.textureID.has_value())
        return;

    sf::RectangleShape shape({ Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.15f });
    shape.setTexture(TextureManager::instance().get(info.textureID.value()));
    shape.setPosition(info.position.x, info.position.y - 2 * info.size.y - Constants::MARGIN);
    m_weaponImages.push_back(std::move(shape));

    auto& btn = m_buttons[info.id];
    m_weaponButtons.emplace(info.type.value(), &btn);
}
