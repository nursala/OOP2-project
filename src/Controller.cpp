#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "ResourseInc/SoundManager.h"
#include "ResourseInc/TextureManager.h"

Controller::Controller()
	: m_window(sf::VideoMode(1900, 1200), "SFML Application"),
	m_animation(TextureManager::instance().get(TextureID::Player), { 5, 5 }, 0.5f)
{
	SoundManager::instance().play(SoundID::BackgroundMusic);
	m_spriteSheet.setTexture(*TextureManager::instance().get(TextureID::Player));
	m_spriteSheet.setTextureRect(m_animation.getUvRect());
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
	float deltaTime = 0.016f; // محاكاة 60 FPS
	int row = 1;
	bool facingRight = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		facingRight = true;
		row = 2; // صف المشي يمينًا
		m_spriteSheet.move(100 * deltaTime, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		facingRight = false;
		row = 2; // نفس صف المشي
		m_spriteSheet.move(-100 * deltaTime, 0);
	}
	else {
		row = 1; // صف الثبات
	}

	m_animation.update(row, 5, deltaTime, facingRight);
	m_spriteSheet.setTextureRect(m_animation.getUvRect());
}

void Controller::render()
{
	m_window.clear();
	m_window.draw(m_spriteSheet);
	m_window.display();
}