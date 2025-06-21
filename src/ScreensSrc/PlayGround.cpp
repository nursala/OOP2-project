#include "ScreensInc/PlayGround.h"
#include <iostream>
#include "cmath"
#include "CommandInc/SwitchScreenCommand.h"
#include "CommandInc/ExitCommand.h"
//playground.cpp
PlayGround::PlayGround()
{   
    m_view.setCenter({m_world.getPlayer().getPosition().x / 2 ,m_world.getPlayer().getPosition().y / 2});
    m_view.setSize(1300/ 3.f, 1000 / 3.f);

}

void PlayGround::init()
{
	initButtons();
}

void PlayGround::initButtons()
{
    auto [playIt, insertedPlay] = m_buttons.emplace(
        ButtonID::Play,
        Button(sf::Vector2f(20, 20), sf::Vector2f(200, 50), "Play")
    );
   
    playIt->second.setCommand(std::make_unique<SwitchScreenCommand>(
        m_changeScreen, ScreenID::Home
    ));

    auto [exitIt, insertedExit] = m_buttons.emplace(
        ButtonID::Exit,
        Button(sf::Vector2f(20, 20), sf::Vector2f(250, 50), "Exit")
    );
    exitIt->second.setCommand(std::make_unique<ExitCommand>(
    ));
}

void PlayGround::update(sf::RenderWindow& window, float dt)
{
	for (auto& [id, button] : m_buttons) {
		button.updateHover(window);
	}
    sf::Vector2f center = m_world.getPlayer().getPosition();
    sf::Vector2f viewSize = m_view.getSize();
    center.x = std::clamp(center.x, viewSize.x / 2.f, m_world.getMapTextureSize().x - viewSize.x / 2.f);
    center.y = std::clamp(center.y, viewSize.y / 2.f, m_world.getMapTextureSize().y - viewSize.y / 2.f);
	m_view.setCenter(center);
    window.setView(m_view);
    m_world.update(window, dt);
}

void PlayGround::render(sf::RenderWindow& window)
{
    //DebugDraw d(&window);
    //d.SetFlags(b2Draw::e_shapeBit);
    //m_world.getWorld().SetDebugDraw(&d);
    m_world.render(window);
	for (auto& [id, button] : m_buttons) {
		button.render(window);
	}
    m_statusBar.render(window, 10, 100, m_view.getCenter() - m_view.getSize()/2.f);
    //m_world.getWorld().DebugDraw();

}
