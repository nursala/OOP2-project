#include "ScreensInc/HomeScreen.h"
#include "ResourseInc/SoundManager.h"
HomeScreen::HomeScreen()
{
	//m_screenID = ScreenID::Home;
	setBackGroundTexture(TextureID::Enemy);
	initButtons();
}

void HomeScreen::initButtons()
{
    auto [playIt, insertedPlay] = m_buttons.emplace(
        ButtonID::Play,
        Button(sf::Vector2f(20, 20), sf::Vector2f(200, 50), "Play")
    );
    playIt->second.setCallback([this]() {
        m_changeScreen(ScreenID::Game);
        });

    auto [exitIt, insertedExit] = m_buttons.emplace(
        ButtonID::Exit,
        Button(sf::Vector2f(20, 20), sf::Vector2f(250, 50), "Exit")
    );
    exitIt->second.setCallback([this]() {
        exit(0);
        });

    auto [stopMusicIt, insertedStop] = m_buttons.emplace(
        ButtonID::Stop,
        Button(sf::Vector2f(50, 50), sf::Vector2f(300, 50), "Stop")
    );
    stopMusicIt->second.setCallback([this]() {
        SoundManager::instance().pause(SoundID::BackgroundMusic);
        });
}


void HomeScreen::processEvent(sf::Event& event, sf::RenderWindow& window)
{
    for (auto& [id, button] : m_buttons)
        button.handleEvent(event, window);
}

void HomeScreen::update(sf::RenderWindow& window) {
    for (auto& [id, button] : m_buttons)
        button.updateHover(window);
}

void HomeScreen::render(sf::RenderWindow& window)
{
	window.draw(m_backGround);
    for (auto& [id, button] : m_buttons)
        button.render(window);
}