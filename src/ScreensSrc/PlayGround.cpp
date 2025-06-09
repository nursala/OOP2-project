#include "ScreensInc/PlayGround.h"
#include <iostream>

PlayGround::PlayGround()
{
	setBackGroundTexture(TextureID::Player);
	initButtons();
}

void PlayGround::initButtons()
{
    auto [playIt, insertedPlay] = m_buttons.emplace(
        ButtonID::Play,
        Button(sf::Vector2f(20, 20), sf::Vector2f(200, 50), "Play")
    );
    playIt->second.setCallback([this]() {
        m_changeScreen(ScreenID::Home);
        });

    auto [exitIt, insertedExit] = m_buttons.emplace(
        ButtonID::Exit,
        Button(sf::Vector2f(20, 20), sf::Vector2f(250, 50), "Exit")
    );
    exitIt->second.setCallback([this]() {
		std::cout << "Exit button clicked, exiting game." << std::endl;
        });
}

void PlayGround::processEvent(sf::Event& event, sf::RenderWindow& window)
{
	m_buttons.at(ButtonID::Play).handleEvent(event, window);
	m_buttons.at(ButtonID::Exit).handleEvent(event, window);
}

void PlayGround::update(sf::RenderWindow& window) {
    m_buttons.at(ButtonID::Play).updateHover(window);
    m_buttons.at(ButtonID::Exit).updateHover(window);
}

void PlayGround::render(sf::RenderWindow& window)
{
	window.draw(m_backGround);
    m_buttons.at(ButtonID::Play).render(window);
    m_buttons.at(ButtonID::Exit).render(window);
}