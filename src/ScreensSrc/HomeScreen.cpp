#include "ScreensInc/HomeScreen.h"
#include "ScreensInc/ChooseLevelScreen.h"
#include "ScreensInc/Market.h"
#include "ScreensInc/Help.h"
#include "ResourseInc/SoundManger.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/ExitCommand.h"

//-------------------------------------
// Constructor - set background and size
//-------------------------------------
HomeScreen::HomeScreen()
{
    setBackGroundTexture(Constants::TextureID::HOMEPAGE);
    setSize();
}

//-------------------------------------
// Initialize buttons and background music
//-------------------------------------
void HomeScreen::init()
{
    m_generalButtons.clear();

    SoundManger::instance().stop(Constants::SoundID::SENARIO);
    SoundManger::instance().stop(Constants::SoundID::GAMEWINSOUND);
    SoundManger::instance().stop(Constants::SoundID::GAMEOVERSOUND);
    SoundManger::instance().play(Constants::SoundID::MENUMUSIC);
    SoundManger::instance().setVolume(Constants::SoundID::MENUMUSIC, 50.f);

    // Play button - leads to level selection screen
    m_generalButtons.emplace_back(
        Constants::ButtonID::Play,
        "Play",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.2f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<ChooseLevelScreen>>()
    );

    // Market button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Market,
        "Market",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.3f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<Market>>()
    );

    // Help button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Help,
        "Help",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.4f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<Help>>()
    );

    // Exit button
    m_generalButtons.emplace_back(
        Constants::ButtonID::Exit,
        "Exit",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.5f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<ExitCommand>()
    );

    setButtons(m_generalButtons);
}

//-------------------------------------
// Return screen ID
//-------------------------------------
Constants::ScreenID HomeScreen::getScreenID() const
{
    return Constants::ScreenID::Home;
}
