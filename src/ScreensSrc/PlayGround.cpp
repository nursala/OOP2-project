#include "ScreensInc/PlayGround.h"
#include <iostream>
#include <cmath>
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/StopMusicCommand.h"
#include "CommandInc/PushScreenCommand.h"
#include "ResourseInc/SoundManager.h"
#include "ScreensInc/PauseScreen.h"
#include "ScreensInc/GameWin.h"
#include "ScreensInc/GameOver.h"
#include "GameSessionData.h"
#include "Constants.h"
#include "Controller.h"

//-------------------------------------
// PlayGround constructor
PlayGround::PlayGround()
{
	m_view.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
	GameSessionData::instance().setHealth(Constants::PLAYER_MAX_HEALTH); // Reset health at the start of the game
}

void PlayGround::init()
{
	m_generalButtons.clear();
	setIniSound();
	m_generalButtons.emplace_back(
		Constants::ButtonID::Pause,
		"",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.90, Constants::MARGIN),
		sf::Vector2f(Constants::BUTTON_IN_STATUS_BAR, Constants::BUTTON_IN_STATUS_BAR),
		std::make_unique<PushScreenCommand<PauseScreen>>()
	);

    setButtons(m_generalButtons);
    m_buttons.at(Constants::ButtonID::Pause).setTexture(Constants::TextureID::PAUSE);

    setSpecialButtons();
}

//-------------------------------------
// Set special buttons like Sound Off
void PlayGround::setSpecialButtons() {
    auto [stopSound, inserted] = m_buttons.emplace(
        Constants::ButtonID::SoundOff,
        Button({ Constants::BUTTON_IN_STATUS_BAR, Constants::BUTTON_IN_STATUS_BAR },
            { Constants::WINDOW_WIDTH * 0.95f, Constants::MARGIN })
    );

    stopSound->second.setTexture(Constants::TextureID::SOUNDON);
    stopSound->second.setCommand(std::make_unique<StopMusicCommand>(stopSound->second));
}

//-------------------------------------
// Update the game logic and camera
void PlayGround::update(sf::RenderWindow& window, float dt) {
    Screen::update(window, dt);

	sf::Vector2f center = m_world.getPlayer().getPosition();
	sf::Vector2f viewSize = m_view.getSize();
	if (GameSessionData::instance().getEnemies() <= 0)
	{
		Controller::getInstance().pushScreen(std::make_unique<GameWin>());
		SoundManager::instance().mute(true, true); // Mute all sounds
		SoundManager::instance().play(Constants::SoundID::GAMEWINSOUND);
		SoundManager::instance().setVolume(Constants::SoundID::GAMEWINSOUND, 30.f);
	}
	if (GameSessionData::instance().getHealth() <= 0)
	{
		Controller::getInstance().pushScreen(std::make_unique<GameOver>());
		SoundManager::instance().mute(true, true); // Mute all sounds
		SoundManager::instance().play(Constants::SoundID::GAMEOVERSOUND);
		SoundManager::instance().setVolume(Constants::SoundID::GAMEOVERSOUND, 30.f);
	}
	if (GameSessionData::instance().getHealth() <= 20)
	{
		SoundManager::instance().play(Constants::SoundID::HEARTBEAT);
		SoundManager::instance().loop(Constants::SoundID::HEARTBEAT, true);
		SoundManager::instance().setVolume(Constants::SoundID::HEARTBEAT,6000.f);
		//SoundManger::instance().loop(Constants::SoundID::HEARTBEAT, true);
	}
	center.x = std::clamp(center.x, viewSize.x / 2.f, m_world.getMapTextureSize().x - viewSize.x / 2.f);
	center.y = std::clamp(center.y, viewSize.y / 2.f, m_world.getMapTextureSize().y - viewSize.y / 2.f);

	m_view.setCenter(center);
	window.setView(m_view);

    m_statusBar.update();
    m_world.update(window, dt);
}

//-------------------------------------
// Render world and HUD
//-------------------------------------
void PlayGround::render(sf::RenderWindow& window) {
    DebugDraw debugDraw(&window);
    const uint32 flags = b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit;
    debugDraw.SetFlags(flags);

    m_world.getWorld().SetDebugDraw(&debugDraw);
    m_world.render(window);

    window.setView(window.getDefaultView());
    Screen::drawButtons(window);
    m_statusBar.render(window);
}

Constants::ScreenID PlayGround::getScreenID() const
{
	return Constants::ScreenID::Game;
}

void PlayGround::setIniSound()
{
	SoundManager::instance().stop(Constants::SoundID::MENUMUSIC);
	SoundManager::instance().play(Constants::SoundID::GAMEBEGIN);
	SoundManager::instance().play(Constants::SoundID::BACKGROUNDMUSIC);
	SoundManager::instance().loop(Constants::SoundID::BACKGROUNDMUSIC, true);
	SoundManager::instance().setVolume(Constants::SoundID::BACKGROUNDMUSIC, 20.f);
}
