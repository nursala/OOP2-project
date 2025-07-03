#include "ScreensInc/PauseScreen.h"
#include "CommandInc/PopToHomeCommand.h"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/PushScreenCommand.h"
#include "ScreensInc/Market.h"
#include "ScreensInc/Help.h"
#include "ResourseInc/SoundManger.h"
#include "Constants.h"

//-------------------------------------
// PauseScreen constructor
PauseScreen::PauseScreen() {
    setBackGroundTexture(Constants::TextureID::PAUSESCREEN);
    setSize();
}

//-------------------------------------
// Get screen ID
Constants::ScreenID PauseScreen::getScreenID() const {
    return Constants::ScreenID::Pause;
}

//-------------------------------------
// Initialize buttons and pause music
void PauseScreen::init() {
    SoundManger::instance().pause(Constants::SoundID::BACKGROUNDMUSIC);
    m_generalButtons.clear();

    m_generalButtons.emplace_back(Constants::ButtonID::Back, "Continue",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PopScreenCommand>());

    m_generalButtons.emplace_back(Constants::ButtonID::BackToHome, "Back to Home",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PopToHomeCommand>());

    m_generalButtons.emplace_back(Constants::ButtonID::Market, "Market",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.7f, Constants::WINDOW_HEIGHT * 0.5f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<Market>>());

    m_generalButtons.emplace_back(Constants::ButtonID::Help, "Help",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.5f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<Help>>());

    setButtons(m_generalButtons);
}
