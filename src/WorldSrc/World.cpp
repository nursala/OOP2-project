#include "WorldInc/World.h"
#include <iostream>
#include <cmath>
#include "Factory.h"

World::World() :
	m_world(b2Vec2(0.f, 0.f)),
	//m_debugDraw(),
	m_tileMap("map.json"),
	m_light(100.f, 720)
{
	if (!m_mapTexture.loadFromFile("map.png")) {
		throw std::runtime_error("Failed to load map.png!");
	}

	m_player = std::unique_ptr<Player>(
		dynamic_cast<Player*>(Factory::instance().create(TextureID::Player, m_world).release())
	);

	m_enemy = std::unique_ptr<Enemy>(
		dynamic_cast<Enemy*>(Factory::instance().create(TextureID::Enemy, m_world).release())
	);

	m_mapSprite.setTexture(m_mapTexture);
	m_tileMap.createCollisionObjects(m_world, "walls");

	//m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	//m_world.SetDebugDraw(&m_debugDraw);
}

void World::update(sf::RenderWindow& window,float deltaTime) {
	m_world.Step(deltaTime, 8, 3);
	m_player->update(deltaTime);
	m_enemy->update(deltaTime);
	// Update the light system
	sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float angleToMouse = std::atan2(mouseWorld.y - m_player->getPixels().y, mouseWorld.x - m_player->getPixels().x);
	float fov = 3.14f / 3.f;
	m_light.update(m_player->getPixels(), angleToMouse, fov, m_world);
}

void World::render(sf::RenderWindow& window) 
{
	sf::RectangleShape bg({ 1300.f, 1000.f });
	bg.setFillColor(sf::Color::Blue);
	window.draw(bg);

	window.draw(m_mapSprite);
	m_player->render(window);
	m_enemy->render(window);
	m_light.draw(window);
	//m_world.DrawDebugData();
}

const sf::Vector2f World::getPlayerPixels() const
{
	if (m_player) {
		return m_player->getPixels();
	}
	return sf::Vector2f(0.f, 0.f);
}

const sf::Vector2f World::getMapTextureSize() const
{
	if (!m_mapTexture.getSize().x || !m_mapTexture.getSize().y) {
		return sf::Vector2f(0.f, 0.f);
	}
	return sf::Vector2f(static_cast<float>(m_mapTexture.getSize().x), static_cast<float>(m_mapTexture.getSize().y));
}
