#include "ScreensInc/GameOver.h"
#include "ScreensInc/Market.h"
#include "ResourseInc/SoundManger.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/ExitCommand.h"
#include "ScreensInc/ChooseLevelScreen.h"
#include "ScreensInc/Market.h"
#include "ScreensInc/Help.h"
#include "ResourseInc/SoundManger.h"
#include "ScreensInc/Screen.h"
#include "CommandInc/PopToHomeCommand.h"

GameOver::GameOver()
{
	setBackGroundTexture(Constants::TextureID::GAMEOVER);
	setSize();
}

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

Constants::ScreenID GameOver::getScreenID() const
{
	return Constants::ScreenID::GameOver;
}