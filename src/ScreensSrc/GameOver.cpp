#include "ScreensInc/GameOver.h"
#include "CommandInc/PopToHomeCommand.h"
#include "ResourseInc/SoundManger.h"

//-------------------------------------
// Constructor - set background and size
//-------------------------------------
GameOver::GameOver()
{
    setBackGroundTexture(Constants::TextureID::GAMEOVER);
    setSize();
}

//-------------------------------------
// Initialize background music and "Back to Home" button
//-------------------------------------
void GameOver::init()
{
    m_generalButtons.clear();

    SoundManger::instance().play(Constants::SoundID::MENUMUSIC);

    m_generalButtons.emplace_back(
        Constants::ButtonID::BackToHome,
        "Back to Home",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.8f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PopToHomeCommand>()
    );

    setButtons(m_generalButtons);
}

//-------------------------------------
// Return screen ID
//-------------------------------------
Constants::ScreenID GameOver::getScreenID() const
{
    return Constants::ScreenID::GameOver;
}
