#include "ScreensInc/PlayGround.h"
#include <iostream>
#include "cmath"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/StopMusicCommand.h"
#include "ResourseInc/SoundManger.h"
#include "CommandInc/PushScreenCommand.h"
#include "ScreensInc/PauseScreen.h"
#include "ScreensInc/GameWin.h"
#include "ScreensInc/GameOver.h"
#include "GameSessionData.h"

PlayGround::PlayGround()
{
	m_view.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
}

void PlayGround::init()
{
	m_generalButtons.clear();
	SoundManger::instance().stop(Constants::SoundID::MENUMUSIC);
	SoundManger::instance().play(Constants::SoundID::GAMEBEGIN);
	SoundManger::instance().play(Constants::SoundID::BACKGROUNDMUSIC);
	SoundManger::instance().setVolume(Constants::SoundID::BACKGROUNDMUSIC, 10.f);
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

void PlayGround::setSpecialButtons()
{
	auto [stopSound, insertedStop] = m_buttons.emplace(
		Constants::ButtonID::SoundOff,
		Button({ Constants::BUTTON_IN_STATUS_BAR, Constants::BUTTON_IN_STATUS_BAR },
			{ Constants::WINDOW_WIDTH * 0.95, Constants::MARGIN })
	);
	stopSound->second.setTexture(Constants::TextureID::SOUNDON);
	stopSound->second.setCommand(std::make_unique<StopMusicCommand>(stopSound->second));
}

void PlayGround::update(sf::RenderWindow& window, float dt)
{
	Screen::update(window, dt);

	sf::Vector2f center = m_world.getPlayer().getPosition();
	sf::Vector2f viewSize = m_view.getSize();
	if (GameSessionData::instance().getEnemies() <= 0)
	{
		Controller::getInstance().pushScreen(std::make_unique<GameWin>());
		SoundManger::instance().stop(Constants::SoundID::BACKGROUNDMUSIC);
		SoundManger::instance().play(Constants::SoundID::GAMEWINSOUND);
	}
	if (GameSessionData::instance().getHealth() <= 0)
	{
		Controller::getInstance().pushScreen(std::make_unique<GameOver>());
		SoundManger::instance().stop(Constants::SoundID::BACKGROUNDMUSIC);
		SoundManger::instance().play(Constants::SoundID::GAMEOVERSOUND);
	}
	center.x = std::clamp(center.x, viewSize.x / 2.f, m_world.getMapTextureSize().x - viewSize.x / 2.f);
	center.y = std::clamp(center.y, viewSize.y / 2.f, m_world.getMapTextureSize().y - viewSize.y / 2.f);

	m_view.setCenter(center);
	window.setView(m_view);

	m_statusBar.update();
	m_world.update(window, dt);
}

void PlayGround::render(sf::RenderWindow& window)
{
	DebugDraw d(&window);
	uint32 flags = b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit;

	
	d.SetFlags(flags);
	m_world.getWorld().SetDebugDraw(&d);
	m_world.render(window);
	window.setView(window.getDefaultView());
	Screen::drawButtons(window);
	m_statusBar.render(window);
}

Constants::ScreenID PlayGround::getScreenID() const
{
	return Constants::ScreenID::Game;
}
