#include "ScreensInc/PlayGround.h"
#include <iostream>
#include "cmath"
#include "CommandInc/PopScreenCommand.h"
#include "CommandInc/ExitCommand.h"
#include "ResourseInc/SoundManger.h"

PlayGround::PlayGround()
{
	m_view.setSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
}

void PlayGround::init()
{
	SoundManger::instance().stop(Constants::SoundID::MENUMUSIC);
	SoundManger::instance().play(Constants::SoundID::GAMEBEGIN);
	//SoundManger::instance().play(Constants::SoundID::BACKGROUNDMUSIC);
	auto [playIt, insertedPlay] = m_buttons.emplace(
		Constants::ButtonID::Play,
		Button({ Constants::WINDOW_WIDTH * 0.05, Constants::WINDOW_HEIGHT * 0.06 },
			{ Constants::WINDOW_WIDTH * 0.9 , Constants::WINDOW_HEIGHT * 0.1 })
	);
	playIt->second.setTexture(Constants::TextureID::GOTOHOME);
	playIt->second.setCommand(std::make_unique<PopScreenCommand>());

	auto [exitIt, insertedExit] = m_buttons.emplace(
		Constants::ButtonID::Exit,
		Button({ Constants::WINDOW_WIDTH * 0.1, Constants::WINDOW_HEIGHT * 0.1 },
			{ Constants::WINDOW_WIDTH * 0.85 - 100, Constants::WINDOW_HEIGHT * 0.1
			}, "Exit")
	);
	exitIt->second.setCommand(std::make_unique<ExitCommand>());
}

void PlayGround::update(sf::RenderWindow& window, float dt)
{
	Screen::update(window, dt);

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
	DebugDraw d(&window);
	uint32 flags = b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit; // أو فقط e_shapeBit

	
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
