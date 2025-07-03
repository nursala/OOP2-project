#include "ScreensInc/LoadGame.h"
#include "ScreensInc/PlayGround.h"
#include "ResourseInc/SoundManger.h"
#include "CommandInc/PopToHomeCommand.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/PopScreenCommand.h"

// -----------------------------
// LoadGame - implementation of loading screen logic
// -----------------------------

LoadGame::LoadGame()
{
    m_timer = 5.f;
    setBackGroundTexture(Constants::TextureID::LOADGAME);
    setSize();
}

// Initializes the screen (stops menu music and plays loading music)
void LoadGame::init()
{
    m_generalButtons.clear();
    SoundManger::instance().stop(Constants::SoundID::MENUMUSIC);
    SoundManger::instance().play(Constants::SoundID::MATCHMAKINGMUSIC);
    SoundManger::instance().setVolume(Constants::SoundID::MATCHMAKINGMUSIC, 40.f);
}

// Updates countdown timer and transitions to PlayGround screen
void LoadGame::update(sf::RenderWindow& window, float dt)
{
    Screen::update(window, dt);
    m_timer -= dt;
    if (m_timer <= 0.f)
    {
        auto command = PushScreenCommand<PlayGround>();
        command.execute();
    }
}

// Returns screen ID for LoadGame
Constants::ScreenID LoadGame::getScreenID() const
{
    return Constants::ScreenID::LoadGame;
}