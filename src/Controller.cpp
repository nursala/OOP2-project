#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "ResourseInc/SoundManager.h"
#include "ResourseInc/TextureManager.h"

Controller::Controller()
	: m_window(sf::VideoMode(1300, 1000), "SFML Application")
	, m_player(m_world),
	m_world(b2Vec2(0.f, 0.f)) 
{
	SoundManager::instance().play(SoundID::BackgroundMusic);
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Controller::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Controller::update()
{
	float deltaTime = m_clock.restart().asSeconds();
	m_world.Step(deltaTime, 8, 3);
	m_player.update(deltaTime);
}

void Controller::render()
{
	m_window.clear();
	m_player.render(m_window);
	m_window.display();
}