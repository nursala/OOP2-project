#include "ScreensInc/HomeScreen.h"
#include "ResourseInc/SoundManager.h"
#include "CommandInc/SwitchScreenCommand.h"
#include "CommandInc/ExitCommand.h"
#include "CommandInc/StopMusicCommand.h"

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
        Button(sf::Vector2f(20, 20), sf::Vector2f(200, 50), "Play")
    );
    playIt->second.setCommand(std::make_unique<SwitchScreenCommand>(
        m_changeScreen, ScreenID::Game
    ));

    auto [exitIt, insertedExit] = m_buttons.emplace(
        ButtonID::Exit,
        Button(sf::Vector2f(20, 20), sf::Vector2f(250, 50), "Exit")
    );

    exitIt->second.setCommand(std::make_unique<ExitCommand>(
    ));

    auto [stopMusicIt, insertedStop] = m_buttons.emplace(
        ButtonID::Stop,
        Button(sf::Vector2f(50, 50), sf::Vector2f(300, 50), "Stop")
    );
	stopMusicIt->second.setCommand(std::make_unique<StopMusicCommand>());
}
