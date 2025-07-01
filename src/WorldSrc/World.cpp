// ===== World.cpp =====
#include "WorldInc/World.h"
#include "GameObject/ContactListener.h"
#include "GameObject/Gift.h"
#include <iostream>
#include <cmath>
#include "Factory.h"
#include "LevelManager.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManger.h"
#include "GameSessionData.h"

World::World()
	: m_world(b2Vec2(0.f, 0.f)),
	m_tileMap(LevelManager::instance().getCurrentLevelPath())
{
	GameSessionData::instance().getLevelID() = LevelManager::instance().getCurrentLevel();
	m_renderLayers = std::make_unique<RenderLayers>();
	initWorld();
}

void World::initWorld() {
    setMapTexture();
    m_world.SetContactListener(new ContactListener(*this));
    createPlayer();
    createEnemy();
    createGifts();
    setupMap();
    buildAllEdges();
}

void World::setMapTexture() {
    
    switch (LevelManager::instance().getCurrentLevel())
    {
    case Constants::LevelID::EasyMap:
		m_mapSprite.setTexture(*TextureManager::instance().get(Constants::TextureID::EASYMAP));
        break;
    case Constants::LevelID::MediumMap:
		m_mapSprite.setTexture(*TextureManager::instance().get(Constants::TextureID::MEDIUMMAP));
        break;
    case Constants::LevelID::HardMap:
		m_mapSprite.setTexture(*TextureManager::instance().get(Constants::TextureID::HARDMAP));
        break;
    default:
        break;
    }
}

void World::createPlayer() {
	b2Vec2 posb2(100,100);
	Factory::instance().registerType<Player>(
		Constants::TextureID::HANDGUNMOVE,
		std::ref(*this),
		std::ref(posb2)
	);

    m_player = Factory::instance().createAs<Player>(Constants::TextureID::HANDGUNMOVE);
	sf::Vector2f pos = m_tileMap.getPlayerSpawns();
	m_player->setPosition(b2Vec2(pos.x, pos.y));
}

void World::createGifts()
{
	b2Vec2 posb2 = b2Vec2_zero;

    int begin = static_cast<int>(Constants::TextureID::ARMOR);
    for (int i = begin; i < static_cast<int>(Constants::TextureID::SIZE); i++) {
        Factory::instance().registerType<Gift>(Constants::TextureID(i), std::ref(*this),  std::ref(posb2) , Constants::TextureID(i));
    }
	auto& giftPositions = m_tileMap.getGiftSpawns();
	int giftsTypeCount = static_cast<int>(Constants::GiftType::SIZE);
	for (const auto& pos : giftPositions)
	{
        createGift(static_cast<Constants::GiftType>(rand() % giftsTypeCount), b2Vec2(pos.x, pos.y));
	}
}

void World::createGift(Constants::GiftType type,b2Vec2 pos)
{
    auto textureId = static_cast<Constants::TextureID>(static_cast<int>(type)+2);
    m_gifts.push_back(Factory::instance().createAs<Gift>(textureId));
    m_gifts.back()->setType(type);
    m_gifts.back()->setPosition(pos);
}

void World::createEnemy()
{
	b2Vec2 posb2 = b2Vec2_zero;

	auto& enemyPositions = m_tileMap.getEnemySpawns();

	GameSessionData::instance().getEnemies() = static_cast<int>(enemyPositions.size());

    Factory::instance().registerType<Enemy>(
        Constants::TextureID::HANDGUNMOVE,
        std::ref(*this),
		std::ref(posb2),
        std::cref(m_tileMap),
        std::cref(*m_player)
    );

	//std::cout << "Enemies size: " << enemyPositions.size() << std::endl;

    for (int i = 0; i < enemyPositions.size(); ++i)
    {
        //int randomIQ = rand() % 10 + 1;

        auto enemy = Factory::instance().createAs<Enemy>(Constants::TextureID::HANDGUNMOVE);
        enemy->setPosition(b2Vec2(enemyPositions[i].x, enemyPositions[i].y));
        m_enemies.push_back(std::move(enemy));
    }
}

void World::setupMap() {
	m_tileMap.createCollisionObjects(m_world, "walls");
}

void World::update(sf::RenderWindow& window, float deltaTime) {
	calcNearlyEdge(window);
	

	// Step physics
	m_world.Step(deltaTime, 8, 3);

	// Update player
	m_player->update(deltaTime);
	m_player->rotateTowardMouse(window);

	//m_player->makeVisble();
	for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
		(*it)->update(deltaTime);
		if ((*it)->isDestroyed()) {
			(*it)->setDestroyed(true);
			it = m_bullets.erase(it);
		}
		else ++it;
	}

	// Update enemies
	for (auto enemy = m_enemies.begin(); enemy != m_enemies.end();)
	{
		if ((*enemy)->isDestroyed()) {
			enemy = m_enemies.erase(enemy);
			SoundManger::instance().play(Constants::SoundID::ENEMYDEATH);
		}
		else {
			(*enemy)->update(deltaTime);
			++enemy;
		}
	}

	// Update bullets


	// Update gifts
	for (auto it = m_gifts.begin(); it != m_gifts.end(); ) {
		it->get()->update(deltaTime);
		if ((*it)->isDestroyed()) {
			it = m_gifts.erase(it);
		}
		else ++it;
	}
	//m_player->makeVisble(true);
	m_renderLayers->setView(window.getView());

}

void World::updateBullets(float deltaTime) {
	for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
		(*it)->update(deltaTime);
		if ((*it)->isDestroyed()) {
			it = m_bullets.erase(it);
		}
		else ++it;
	}
}

void World::render(sf::RenderWindow& window) {

	m_renderLayers->clear();
	m_renderLayers->drawBackground(m_mapSprite);
	m_player->render(*m_renderLayers);

	for (auto& enemy : m_enemies)
		enemy->render(*m_renderLayers);

	for (auto& gift : m_gifts)
		 gift->render(*m_renderLayers);

	for (auto& bullet : m_bullets)
		bullet->render(*m_renderLayers);

	m_renderLayers->display();
	m_renderLayers->renderFinal(window);
}

b2World& World::getWorld() {
	return m_world;
}

void World::addBullets(std::vector<std::unique_ptr<Bullet>> bullets) {
	for (auto& bullet : bullets)
	{
		m_bullets.push_back(std::move(bullet));
	}
}

const sf::Vector2f World::getMapTextureSize() const {
    const sf::Texture* texture = m_mapSprite.getTexture();
    if (!texture)
        return sf::Vector2f(0.f, 0.f);

    sf::Vector2u size = texture->getSize();
    return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

const Player& World::getPlayer() const {
	return *m_player;
}

std::vector<Enemy*> World::getEnemies() const {
	std::vector<Enemy*> result;
	for (const auto& e : m_enemies)
		result.push_back(e.get());
	return result;
}

void World::buildAllEdges()
{
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


void World::calcNearlyEdge(sf::RenderWindow& window)
{
    sf::Vector2f viewCenter = window.getView().getCenter(); 
    sf::Vector2f viewSize = window.getView().getSize();      

	sf::Vector2f lightPos = viewCenter;
	float radius = std::max(viewSize.x, viewSize.y) * 0.6f;
	float rangeSq = radius * radius;

	m_closeEdges.clear();
	for (const auto& edge : m_allEdges) {
		sf::Vector2f p1 = edge.m_origin;
		sf::Vector2f p2 = edge.point(1.f);
		sf::Vector2f ab = p2 - p1;
		sf::Vector2f ap = lightPos - p1;

		float abDotAb = ab.x * ab.x + ab.y * ab.y;
		if (abDotAb == 0) continue;

		float t = std::max(0.f, std::min(1.f, (ap.x * ab.x + ap.y * ab.y) / abDotAb));
		sf::Vector2f closestPoint = p1 + ab * t;

		float dx = closestPoint.x - lightPos.x;
		float dy = closestPoint.y - lightPos.y;
		float distSq = dx * dx + dy * dy;

		if (distSq <= rangeSq) {
			m_closeEdges.push_back(edge);
		}
	}
}

void World::DebugEdge(sf::RenderWindow& window)
{
	for (const auto& edge : m_allEdges) {
		sf::Vector2f p1 = edge.m_origin;
		sf::Vector2f p2 = edge.point(1.f);
		sf::Vector2f direction = p2 - p1;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		sf::RectangleShape rect;
		rect.setSize({ length, 2.f });
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(p1);
		rect.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159f);
		window.draw(rect);
	}

	for (const auto& edge : m_closeEdges) {
		sf::Vector2f p1 = edge.m_origin;
		sf::Vector2f p2 = edge.point(1.f);
		sf::Vector2f direction = p2 - p1;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		sf::RectangleShape rect;
		rect.setSize({ length, 3.f });
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(p1);
		rect.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159f);
		window.draw(rect);
	}
}
