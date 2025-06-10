#include "ScreensInc/PlayGround.h"
#include <iostream>
#include "cmath"
//playground.cpp
PlayGround::PlayGround()
{   
	initButtons();
    m_view.setCenter({m_world.getPlayerPixels().x / 2 ,m_world.getPlayerPixels().y / 2});
    m_view.setSize(1300/ 3.f, 1000 / 3.f);
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

void PlayGround::update(sf::RenderWindow& window, float dt)
{
	for (auto& [id, button] : m_buttons) {
		button.updateHover(window);
	}
    sf::Vector2f center = m_world.getPlayerPixels();
    sf::Vector2f viewSize = m_view.getSize();
    center.x = std::clamp(center.x, viewSize.x / 2.f, m_world.getMapTextureSize().x - viewSize.x / 2.f);
    center.y = std::clamp(center.y, viewSize.y / 2.f, m_world.getMapTextureSize().y - viewSize.y / 2.f);
	m_view.setCenter(center);
    m_world.update(window, dt);
}

void PlayGround::render(sf::RenderWindow& window)
{
    window.setView(m_view);
	m_world.render(window);
    window.setView(window.getDefaultView());
	for (auto& [id, button] : m_buttons) {
		button.render(window);
	}
}

//void PlayGround::processEvent(sf::Event& event, sf::RenderWindow& window) {
//    window.setView(window.getDefaultView());
//
//    for (auto& [id, button] : m_buttons) {
//        button.handleEvent(event, window);
//    }
//}
//
