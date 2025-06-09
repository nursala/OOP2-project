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
	: m_window(sf::VideoMode(1300, 1000), "SFML Application"),
	m_world(b2Vec2(0.f, 0.f)),
	m_debugDraw(&m_window),
	m_tileMap("map.json"),
	m_light(100.f, 720)
{
	m_changeScreen = [this](ScreenID id) {
		m_nextScreen = id;
		};

	setScreen(ScreenID::Home); 

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
		m_screens.top()->update(m_window);
	sf::Vector2f center = m_player->getPixels();

	sf::Vector2f viewSize = m_view.getSize();
	center.x = std::clamp(center.x, viewSize.x / 2.f, (float)m_mapTexture.getSize().x - viewSize.x / 2.f);
	center.y = std::clamp(center.y, viewSize.y / 2.f, (float)m_mapTexture.getSize().y - viewSize.y / 2.f);
	m_view.setCenter(center);
	//m_window.setView(m_view);
	m_world.Step(deltaTime, 8, 3);
	m_player->update(deltaTime);
	sf::Vector2f mouseWorld = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	float angleToMouse = std::atan2(mouseWorld.y - m_player->getPixels().y, mouseWorld.x - m_player->getPixels().x);
	float fov = 3.14f / 3.f;

	m_light.update(m_player->getPixels(), angleToMouse, fov, m_world);
	m_enemy->update(deltaTime);
	std::cout << "size of screens stack: " << m_screens.size() << std::endl;
}

void Controller::render()
{
	m_window.clear();
	if (!m_screens.empty())
		m_screens.top()->render(m_window);
	/*m_window.draw(m_mapSprite);
	m_light.draw(m_window);
	m_player->render(m_window);
	m_enemy->render(m_window);
	m_world.DebugDraw();*/
	m_window.display();
}