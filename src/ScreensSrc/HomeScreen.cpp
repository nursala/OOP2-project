#include "ScreensInc/HomeScreen.h"
#include "ScreensInc/Market.h"
#include "ResourseInc/SoundManager.h"
#include "CommandInc/PushScreenCommand.h"
#include "CommandInc/ExitCommand.h"
#include "CommandInc/StopMusicCommand.h"
#include "ScreensInc/PlayGround.h"
#include "CommandInc/PopToHomeCommand.h"

HomeScreen::HomeScreen()
{
	setBackGroundTexture(TextureID::Enemy);
}

void HomeScreen::init() {
    initButtons();
}

void HomeScreen::initButtons()
{
    auto [playIt, insertedPlay] = m_buttons.emplace(
        ButtonID::Play,
        Button(sf::Vector2f(200, 50), sf::Vector2f(200, 100), "Play")
    );
    playIt->second.setCommand(std::make_unique<PushScreenCommand<Market>>());

    auto [exitIt, insertedExit] = m_buttons.emplace(
        ButtonID::Exit,
        Button(sf::Vector2f(200, 50), sf::Vector2f(200, 160), "Exit")
    );
    exitIt->second.setCommand(std::make_unique<ExitCommand>());

    auto [stopMusicIt, insertedStop] = m_buttons.emplace(
        ButtonID::Stop,
        Button(sf::Vector2f(200, 50), sf::Vector2f(200, 220), "Stop")
    );
    stopMusicIt->second.setCommand(std::make_unique<StopMusicCommand>());
}

ScreenID HomeScreen::getScreenID() const
{
	return ScreenID::Home;
}