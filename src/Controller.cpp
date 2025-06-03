//controller.cpp
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "ResourseInc/SoundManager.h"
#include "ResourseInc/TextureManager.h"
#include <iostream>
#include <cmath>
#include "Factory.h"

Controller::Controller()
	: m_window(sf::VideoMode(1300, 1000), "SFML Application"),
	m_world(b2Vec2(0.f, 0.f)),
	m_debugDraw(&m_window),
	m_tileMap("map.json"),
	m_light(100.f, 720)
{

	SoundManager::instance().play(SoundID::BackgroundMusic);
	m_window.setFramerateLimit(60);
	if (!m_mapTexture.loadFromFile("map.png")) {
		std::cerr << "Failed to load map.png!\n";
		std::exit(-1);
	}
	m_player = std::unique_ptr<Player>(
		dynamic_cast<Player*>(Factory::instance().create(TextureID::Player, m_world).release())
	);

	m_enemy = std::unique_ptr<Enemy>(
		dynamic_cast<Enemy*>(Factory::instance().create(TextureID::Enemy, m_world).release())
	);

	m_view.setCenter({ m_player->getPixels().x / 2 ,m_player->getPixels().y / 2 });
	m_view.setSize(m_window.getSize().x / 3.f, m_window.getSize().y / 3.f);
	m_mapSprite.setTexture(m_mapTexture);
	m_tileMap.createCollisionObjects(m_world, "walls");
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	m_world.SetDebugDraw(&m_debugDraw);

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
	sf::Vector2f center = m_player->getPixels();

	sf::Vector2f viewSize = m_view.getSize();
	center.x = std::clamp(center.x, viewSize.x / 2.f, (float)m_mapTexture.getSize().x - viewSize.x / 2.f);
	center.y = std::clamp(center.y, viewSize.y / 2.f, (float)m_mapTexture.getSize().y - viewSize.y / 2.f);
	m_view.setCenter(center);
	m_window.setView(m_view);
	m_world.Step(deltaTime, 8, 3);
	m_player->update(deltaTime);
	sf::Vector2f mouseWorld = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	float angleToMouse = std::atan2(mouseWorld.y - m_player->getPixels().y, mouseWorld.x - m_player->getPixels().x);
	float fov = 3.14f / 3.f; 

	m_light.update(m_player->getPixels(), angleToMouse, fov, m_world);
	m_enemy->update(deltaTime);
}

void Controller::render()
{
	m_window.clear();
	m_window.draw(m_mapSprite);       
	m_light.draw(m_window);           
	m_player->render(m_window);          
	m_enemy->render(m_window);
	m_world.DebugDraw();
	m_window.display();
}