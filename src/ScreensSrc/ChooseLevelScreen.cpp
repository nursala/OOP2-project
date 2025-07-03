#include "ScreensInc/ChooseLevelScreen.h"
#include "CommandInc/StartGameCommand.h"
#include "LevelManager.h"
#include "CommandInc/PopScreenCommand.h"
#include "ResourseInc/TextureManager.h"

//-------------------------------------
// Constructor - sets background and size
//-------------------------------------
ChooseLevelScreen::ChooseLevelScreen()
    : Screen()
{
    setBackGroundTexture(Constants::TextureID::CHOOSEMAP);
    setSize();
}

//-------------------------------------
// Initialize buttons and map previews
//-------------------------------------
void ChooseLevelScreen::init()
{
    m_generalButtons.clear();

    // Easy level button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Easy,
        "Easy",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<StartGameCommand>(Constants::LevelID::EasyMap),
        Constants::TextureID::EASYMAP,
        std::nullopt,
        sf::Color::Green
    );

    // Medium level button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Medium,
        "Medium",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.4f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<StartGameCommand>(Constants::LevelID::MediumMap),
        Constants::TextureID::MEDIUMMAP
    );

    // Hard level button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Hard,
        "Hard",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<StartGameCommand>(Constants::LevelID::HardMap),
        Constants::TextureID::HARDMAP,
        std::nullopt,
        sf::Color::Red
    );

    // Back button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Back,
        "Back",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
        std::make_unique<PopScreenCommand>()
    );

    // Load preview images above each level button
    for (auto& info : m_generalButtons)
    {
        if (info.textureID.has_value())
        {
            sf::RectangleShape shape({ info.size.x, Constants::WINDOW_HEIGHT * 0.3f });
            shape.setTexture(TextureManager::instance().get(info.textureID.value()));
            shape.setPosition(info.position.x, info.position.y - 4 * info.size.y - Constants::MARGIN);
            m_level.push_back(std::move(shape));
        }
    }

    setButtons(m_generalButtons);
}

//-------------------------------------
// Return screen ID
//-------------------------------------
Constants::ScreenID ChooseLevelScreen::getScreenID() const
{
    return Constants::ScreenID::ChooseLevel;
}

//-------------------------------------
// Render background, level previews, and buttons
//-------------------------------------
void ChooseLevelScreen::render(sf::RenderWindow& window)
{
    Screen::render(window);
    for (const auto& level : m_level)
    {
        window.draw(level);
    }
}
