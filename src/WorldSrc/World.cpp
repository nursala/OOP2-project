#include "WorldInc/World.h"
#include <iostream>
#include <cmath>
#include "Factory.h"

World::World() :
	m_world(b2Vec2(0.f, 0.f)),
	m_tileMap("map.json"),
	m_light({ 2400, 2400})
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

	m_gift = std::unique_ptr<Gift>(
		dynamic_cast<Gift*>(Factory::instance().create(TextureID::Gift, m_world).release())
	);
	m_mapSprite.setTexture(m_mapTexture);
	m_tileMap.createCollisionObjects(m_world, "walls");

	buildAllEdges();

	//m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	//m_world.SetDebugDraw(&m_debugDraw);
	m_player->setLight(m_light.getPlayerVision());
	m_player->setWeaponLight(m_light.getWeaponLight());
}

void World::update(sf::RenderWindow& window, float deltaTime) {
	m_world.Step(deltaTime, 8, 3);
	m_player->update(deltaTime);
	m_enemy->update(deltaTime);

	// زاوية الضوء حسب اتجاه الماوس
	sf::Vector2f playerPos = m_player->getPixels();
	sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float angleToMouse = std::atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x);

	// نحسب الحواف القريبة فقط (closeEdges)
	m_closeEdges.clear();
	sf::Vector2f lightPos = m_light.getPlayerVision()->getPosition();
	float rangeSq = m_light.getPlayerVision()->getRange() * m_light.getPlayerVision()->getRange();

	for (const auto& edge : m_allEdges) {
		sf::Vector2f p1 = edge.m_origin;
		sf::Vector2f p2 = edge.point(1.f);

		float dx1 = p1.x - lightPos.x, dy1 = p1.y - lightPos.y;
		float dx2 = p2.x - lightPos.x, dy2 = p2.y - lightPos.y;

		if (dx1 * dx1 + dy1 * dy1 <= rangeSq || dx2 * dx2 + dy2 * dy2 <= rangeSq) {
			m_closeEdges.push_back(edge);
		}
	}
	m_light.update(playerPos, mouseWorld);
	// تحديث نظام الإضاءة مع الحواف القريبة
	m_light.updateCastLight( m_closeEdges, m_world);
	sf::Vector2f topLeft = window.getView().getCenter() - window.getView().getSize() / 2.f;

	m_light.setPosition(topLeft); // تحديث موقع منطقة الإضاءة
}

void World::render(sf::RenderWindow& window) 
{

	
	window.draw(m_mapSprite);
	m_light.drawFinalLights(window);
	
	m_player->render(window);
	
	m_enemy->render(window);

	m_light.drawLights(window);

	m_gift->render(window);

	m_world.DebugDraw();

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

void World::buildAllEdges() {
	for (b2Body* body = m_world.GetBodyList(); body != nullptr; body = body->GetNext()) {
		for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext()) {
			if (fixture->GetType() == b2Shape::e_polygon) {
				auto* shape = static_cast<b2PolygonShape*>(fixture->GetShape());
				for (int i = 0; i < shape->m_count; ++i) {
					b2Vec2 v1 = body->GetWorldPoint(shape->m_vertices[i]);
					b2Vec2 v2 = body->GetWorldPoint(shape->m_vertices[(i + 1) % shape->m_count]);
					m_allEdges.emplace_back(
						sf::Vector2f(v1.x * SCALE, v1.y * SCALE),
						sf::Vector2f(v2.x * SCALE, v2.y * SCALE)
					);
				}
			}
		}
	}
}
