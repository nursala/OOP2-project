#include "ScreensInc/GameWin.h"
#include "ResourseInc/SoundManger.h"
#include "ResourseInc/SoundManger.h"
#include "ScreensInc/Screen.h"
#include <CommandInc/PopToHomeCommand.h>

GameWin::GameWin()
{
	setBackGroundTexture(Constants::TextureID::GAMEWIN);
	setSize();
}

void GameWin::init()
{
	m_generalButtons.clear();
	SoundManger::instance().stop(Constants::SoundID::GAMEWINSOUND);
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

Constants::ScreenID GameWin::getScreenID() const
{
	return Constants::ScreenID::GameWin;
}