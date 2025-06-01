#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SoundManager.h"

Controller::Controller() : m_window(sf::VideoMode(800, 600), "SFML Application") 
{
	SoundManager::instance().play(SoundID::BackgroundMusic);
	m_shape.setSize(sf::Vector2f(100, 100));
	m_shape.setPosition(350, 250); // Center the shape in the window
	m_shape.setTexture(&TextureManager::instance().get(TextureID::Kill));
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
	// Update game logic here
}

void Controller::render()
{
	m_window.clear();
	m_window.draw(m_shape);
	m_window.display();
}