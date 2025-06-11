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
	: m_window(sf::VideoMode(1920, 1080), "SFML Application"),
	m_world(b2Vec2(0.f, 0.f)),
	m_debugDraw(&m_window),
	m_tileMap("map.json"),
	m_visionLight(150, 60),
	m_lightingArea(candle::LightingArea::FOG, sf::Vector2f(0.f, 0.f), sf::Vector2f(1920, 1080))
{
	m_radialLight.setRange(25);
	m_radialLight.setFade(true);
	m_radialLight.setColor(sf::Color::Blue);
	m_lightingArea.setAreaColor(sf::Color::Black);
	m_lightingArea.setAreaOpacity(0.8);

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

	m_view.setCenter({ m_player->getPixels().x / 2 , m_player->getPixels().y / 2 });
	m_view.setSize(m_window.getSize().x / 4.f, m_window.getSize().y / 4.f);
	m_mapSprite.setTexture(m_mapTexture);
	m_tileMap.createCollisionObjects(m_world, "walls");
	m_radialLight.setPosition(m_player->getPixels());
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	m_world.SetDebugDraw(&m_debugDraw);
	for (b2Body* body = m_world.GetBodyList(); body != nullptr; body = body->GetNext()) {
		for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext()) {
			b2Shape::Type shapeType = fixture->GetType();
			if (shapeType == b2Shape::e_polygon) {
				b2PolygonShape* poly = static_cast<b2PolygonShape*>(fixture->GetShape());
				const int count = poly->m_count;
				for (int i = 0; i < count; ++i) {
					b2Vec2 v1 = body->GetWorldPoint(poly->m_vertices[i]);
					b2Vec2 v2 = body->GetWorldPoint(poly->m_vertices[(i + 1) % count]);
					candle::Edge edge(
						sf::Vector2f(v1.x * SCALE, v1.y * SCALE),
						sf::Vector2f(v2.x * SCALE, v2.y * SCALE)
					);
					m_lightEdges.emplace_back(edge);
				}
			}
		}
	}



}

void Controller::run()
{
	while (m_window.isOpen()) {
		processEvents();
		update();
		render();
	}
}


void Controller::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
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
	m_enemy->update(deltaTime);

	sf::Vector2f currentPos = m_player->getPixels();
	sf::Vector2f mouseWorld = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	float angle = std::atan2(mouseWorld.y - currentPos.y, mouseWorld.x - currentPos.x) * 180.f / 3.14159265f;
	sf::Vector2f playerPos = m_player->getPixels();
	closeEdges.clear();
	for (const auto& edge : m_lightEdges) {
		sf::Vector2f p1 = edge.m_origin;
		sf::Vector2f p2 = edge.point(1.f);
		sf::Vector2f lightPos = m_visionLight.getPosition();
		float rangeSq = m_visionLight.getRange() * m_visionLight.getRange();

		// نحسب المسافة من كل طرف للحافة إلى الضوء
		float dx1 = p1.x - lightPos.x, dy1 = p1.y - lightPos.y;
		float dx2 = p2.x - lightPos.x, dy2 = p2.y - lightPos.y;
		float distSq1 = dx1 * dx1 + dy1 * dy1;
		float distSq2 = dx2 * dx2 + dy2 * dy2;

		// إذا أي طرف داخل النطاق نضيف الحافة
		if (distSq1 <= rangeSq || distSq2 <= rangeSq) {
			closeEdges.push_back(edge);
		}
	}


	for (auto* fixture : hitFixtures) {
		std::cout << "Enemy out of light at position: " << std::endl;
		if (fixture->GetUserData().pointer != 0) {
			Enemy* enemy = reinterpret_cast<Enemy*>(fixture->GetUserData().pointer);
			if (enemy) {
				enemy->setVisible(false);
			}
		}
	}
	m_radialLight.setPosition(playerPos);
	m_visionLight.update(playerPos, angle);
	m_visionLight.castLightCustom(closeEdges.begin(), closeEdges.end(), m_world, hitFixtures);

	for (auto* fixture : hitFixtures) {
		std::cout << "Enemy hit by light at position: " << std::endl;
		if (fixture->GetUserData().pointer != 0) {
			Enemy* enemy = reinterpret_cast<Enemy*>(fixture->GetUserData().pointer);
			if (enemy) {
				enemy->setVisible(true);
			}
		}
	}
	m_lightingArea.setPosition({ m_view.getCenter().x - m_view.getSize().x / 2, m_view.getCenter().y - m_view.getSize().y / 2 });

}
void Controller::render()
{

	// مسح الإضاءة السابقة
	m_lightingArea.clear();

	// رسم جميع الأضواء داخل LightingArea
	// ضوء شعاعي عام
	// يمكن لاحقًا إضافة: سلاح، أعداء، هدايا ... إلخ

	m_lightingArea.draw(m_visionLight);

	m_lightingArea.draw(m_radialLight);

	// تجهيز النتيجة النهائية
	m_lightingArea.display();

	// مسح الشاشة
	m_window.clear();

	// رسم العالم (الخريطة والكائنات)
	m_window.draw(m_mapSprite);
	m_window.draw(m_lightingArea);

	m_player->render(m_window);
	m_enemy->render(m_window);

	// رسم الإضاءة النهائية فوق العالم (BlendMin يعطي تأثير "ضوء وسط ظلام")
	// رسم الإضاءة الشعاعية
	m_visionLight.setIntensity(0.4);

	m_window.draw(m_radialLight);
	m_window.draw(m_visionLight);
	m_window.draw(m_player->getVisionLight());





	// رسم الكولجن (debug)
	m_world.DebugDraw();

	// عرض كل شيء
	m_window.display();
}
