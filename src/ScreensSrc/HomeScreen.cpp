#include "ScreensInc/HomeScreen.h"
#include "ScreensInc/Market.h"
#include "ResourseInc/SoundManager.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/ExitCommand.h"
#include "ScreensInc/ChooseLevelScreen.h"
#include "ScreensInc/Market.h"
#include "ScreensInc/Help.h"
#include "ScreensInc/Screen.h"

HomeScreen::HomeScreen()
{
	setBackGroundTexture(Constants::TextureID::HOMEPAGE);
	setSize();
}

void HomeScreen::init()
{
	m_generalButtons.clear();

	m_generalButtons.emplace_back(
		Constants::ButtonID::Play,
		"Play",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.2f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
		std::make_unique<PushScreenCommand<ChooseLevelScreen>>()
	);

	m_generalButtons.emplace_back(
		Constants::ButtonID::Market,
		"Market",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.3f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
		std::make_unique<PushScreenCommand<Market>>()
	);


	m_generalButtons.emplace_back(
		Constants::ButtonID::Help,
		"Help",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.4f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
		std::make_unique<PushScreenCommand<Help>>()
	);

	m_generalButtons.emplace_back(
		Constants::ButtonID::Exit,
		"Exit",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.5f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
		std::make_unique<ExitCommand>()
	);

	setButtons(m_generalButtons);
}

Constants::ScreenID HomeScreen::getScreenID() const
{
	return Constants::ScreenID::Home;
}