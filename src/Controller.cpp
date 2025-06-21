//controller.cpp
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "ResourseInc/SoundManager.h"
#include "ResourseInc/TextureManager.h"
#include <iostream>
#include <cmath>
#include "Factory.h"
#include "ScreensInc/HomeScreen.h"
#include "ScreensInc/PlayGround.h"

Controller::Controller()
	: m_window(sf::VideoMode(1280, 720), "SFML Application")
{
	m_changeScreen = [this](ScreenID id) {
		m_nextScreen = id;
		};
	setScreen(ScreenID::Game);
	//SoundManager::instance().play(SoundID::BackgroundMusic);
	m_window.setFramerateLimit(60);
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		if (m_nextScreen.has_value()) {
			removeScreen();
			setScreen(m_nextScreen.value());
			m_nextScreen.reset();
		}
		processEvents();
		update();
		render();
	}
}

void Controller::setScreen(ScreenID screen)
{
	std::unique_ptr<Screen> screenPtr;

	switch (screen)
	{
	case ScreenID::Home:
		screenPtr = std::make_unique<HomeScreen>();
		break;
	case ScreenID::Game:
		screenPtr = std::make_unique<PlayGround>();
		break;
	}

	if (screenPtr)
	{
		screenPtr->setScreenAction(m_changeScreen);
		m_screens.push(std::move(screenPtr));
	}
}

void Controller::removeScreen()
{
	if (!m_screens.empty())
	{
		m_screens.pop();
	}
}

void Controller::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();

		if (!m_screens.empty())
			m_screens.top()->processEvent(event, m_window);
	}
}

void Controller::update()
{
	float deltaTime = m_clock.restart().asSeconds();
	if (!m_screens.empty())
		m_screens.top()->update(m_window, deltaTime);
}

void Controller::render()
{
	m_window.clear();
	if (!m_screens.empty())
		m_screens.top()->render(m_window);
	m_window.display();
}