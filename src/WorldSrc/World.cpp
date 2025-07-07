// ===== World.cpp =====
#include "WorldInc/World.h"
#include "ContactListener.h"
#include "GameObject/Gift.h"
#include <iostream>
#include <cmath>
#include "Factory.h"
#include "LevelManager.h"
#include "ResourseInc/TextureManager.h"
#include "ResourseInc/SoundManager.h"
#include "GameSessionData.h"

//-------------------------------------
// World Constructor
World::World()
	: m_world(b2Vec2(0.f, 0.f)),
	m_tileMap(LevelManager::instance().getCurrentLevelPath())
{
	GameSessionData::instance().setLevelID(LevelManager::instance().getCurrentLevel());
	m_renderLayers = std::make_unique<RenderLayers>();
	initWorld();
}

//-------------------------------------
// Initialize the Box2D world and game entities
void World::initWorld() {
	setMapTexture();
	m_world.SetContactListener(new ContactListener(*this));
	createPlayer();
	createEnemy();
	createGifts();
	setupMap();
	buildAllEdges();
}

//-------------------------------------
// Set map texture based on the selected level
void World::setMapTexture() {
	m_mapSprite.setTexture(*TextureManager::instance().get(
		Constants::LevelTexture.at(LevelManager::instance().getCurrentLevel())));
}

//-------------------------------------
// Create player entity
void World::createPlayer() {
	const sf::Vector2f pos = m_tileMap.getPlayerSpawns();
	const b2Vec2 posB2(pos.x, pos.y);
	m_player = Factory::instance().createAs<Player>(Constants::EntityType::Player, *this, posB2);
}

//-------------------------------------
// Create gift entities at spawn positions
void World::createGifts() {
	const auto giftPositions = m_tileMap.getGiftSpawns();

	for (const auto& pos : giftPositions) {
		Constants::GiftType type;

		int chance = rand() % 100;
		if (chance < 30) {
			type = Constants::GiftType::ARMOR;
		}
		else if (chance < 60) {
			type = Constants::GiftType::HEALTH;
		}

		else {
			std::vector<Constants::GiftType> otherTypes;

			const int giftTypeCount = static_cast<int>(Constants::GiftType::SIZE);
			for (int i = 0; i < giftTypeCount; ++i) {
				auto gift = static_cast<Constants::GiftType>(i);
				if (gift != Constants::GiftType::ARMOR && gift != Constants::GiftType::HEALTH) {
					otherTypes.push_back(gift);
				}
			}

			if (!otherTypes.empty()) {
				type = otherTypes[rand() % otherTypes.size()];
			}
			else {
				type = Constants::GiftType::ARMOR;
			}
		}

		const b2Vec2 posB2(pos.x, pos.y);
		auto gift = Factory::instance().createAs<Gift>(Constants::EntityType::Gift, *this, pos, type);
		m_gifts.push_back(std::move(gift));
	}
}

//-------------------------------------
// Create enemy entities with random weapons
void World::createEnemy() {
	const auto& enemyPositions = m_tileMap.getEnemySpawns();
	GameSessionData::instance().setEnemies(static_cast<int>(enemyPositions.size()));
	const int weaponsCount = static_cast<int>(Constants::WeaponType::Size);

	for (const auto& pos : enemyPositions) {
		Constants::WeaponType weaponType;
		if (rand() % 100 < 70) {
			// 70% chance to get a HandGun
			weaponType = Constants::WeaponType::HandGun;
		}
		else {
			// 30% chance to get a random weapon (excluding handgun)
			int otherWeaponCount = weaponsCount - 1;
			int randomIndex = rand() % otherWeaponCount;
			weaponType = static_cast<Constants::WeaponType>(randomIndex >= static_cast<int>(Constants::WeaponType::HandGun)
				? randomIndex + 1 : randomIndex);
		}

		const b2Vec2 posB2(pos.x, pos.y);
		auto enemy = Factory::instance().createAs<Enemy>(Constants::EntityType::Enemy, *this, pos, m_tileMap, *m_player, weaponType);
		m_enemies.push_back(std::move(enemy));
	}

}

//-------------------------------------
// Setup map by creating wall collision objects
void World::setupMap() {
	m_tileMap.createCollisionObjects(m_world, "walls");
}

//-------------------------------------
// Update the game world each frame
void World::update(sf::RenderWindow& window, const float deltaTime) {
	calcNearlyEdge(window);
	m_world.Step(deltaTime, 8, 3);

	m_player->update(deltaTime);
	m_player->rotateTowardMouse(window);

	updateBullets(deltaTime);
	updateEnemies(deltaTime);
	updateGifts(deltaTime);

	m_renderLayers->setView(window.getView());
}

//-------------------------------------
// Update all bullets and remove destroyed ones
void World::updateBullets(float deltaTime) {
	for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
		(*it)->update(deltaTime);
		if ((*it)->isDestroyed())
			it = m_bullets.erase(it);
		else ++it;
	}
}

//-------------------------------------
// Update all enemies and handle their destruction
void World::updateEnemies(const float deltaTime) {
	for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
		if ((*it)->isDestroyed()) {
			it = m_enemies.erase(it);
			GameSessionData::instance().setEnemies(GameSessionData::instance().getEnemies() - 1);
			GameSessionData::instance().setMoney(GameSessionData::instance().getMoney() + 50);
			SoundManager::instance().play(Constants::SoundID::ENEMYDEATH);
		}
		else {
			(*it)->update(deltaTime);
			++it;
		}
	}
}

//-------------------------------------
// Update all gifts and remove collected ones
void World::updateGifts(const float deltaTime) {
	for (auto it = m_gifts.begin(); it != m_gifts.end(); ) {
		(*it)->update(deltaTime);
		if ((*it)->isDestroyed())
			it = m_gifts.erase(it);
		else ++it;
	}
}

//-------------------------------------
// Render all game objects to the window
void World::render(sf::RenderWindow& window) {
	m_renderLayers->clear();
	m_renderLayers->drawBackground(m_mapSprite);

	m_player->render(*m_renderLayers);
	for (const auto& enemy : m_enemies)
		enemy->render(*m_renderLayers);
	for (const auto& gift : m_gifts)
		gift->render(*m_renderLayers);
	for (const auto& bullet : m_bullets)
		bullet->render(*m_renderLayers);

	m_renderLayers->display();
	m_renderLayers->renderFinal(window);
}

//-------------------------------------
// Return reference to Box2D world
b2World& World::getWorld() {
	return m_world;
}

//-------------------------------------
// Add bullets to be managed by the world
void World::addBullets(std::vector<std::unique_ptr<Bullet>> bullets) {
	for (auto& bullet : bullets)
		m_bullets.push_back(std::move(bullet));
}

//-------------------------------------
// Get the size of the background texture
const sf::Vector2f World::getMapTextureSize() const {
	const sf::Texture* texture = m_mapSprite.getTexture();
	if (!texture)
		return sf::Vector2f(0.f, 0.f);

	const sf::Vector2u size = texture->getSize();
	return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

//-------------------------------------
// Get const reference to the player
const Player& World::getPlayer() const {
	return *m_player;
}

//-------------------------------------
// Return a list of enemy pointers
std::vector<Enemy*> World::getEnemies() const {
	std::vector<Enemy*> result;
	for (const auto& e : m_enemies)
		result.push_back(e.get());
	return result;
}

//-------------------------------------
// Extract and store all map edge lines
void World::buildAllEdges() {
	for (b2Body* body = m_world.GetBodyList(); body != nullptr; body = body->GetNext()) {
		for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext()) {
			if (fixture->GetType() == b2Shape::e_polygon) {
				auto* shape = static_cast<b2PolygonShape*>(fixture->GetShape());
				for (int i = 0; i < shape->m_count; ++i) {
					const b2Vec2 v1 = body->GetWorldPoint(shape->m_vertices[i]);
					const b2Vec2 v2 = body->GetWorldPoint(shape->m_vertices[(i + 1) % shape->m_count]);
					m_allEdges.emplace_back(
						sf::Vector2f(v1.x * SCALE, v1.y * SCALE),
						sf::Vector2f(v2.x * SCALE, v2.y * SCALE)
					);
				}
			}
		}
	}
}

//-------------------------------------
// Calculate which edges are near the view center
void World::calcNearlyEdge(sf::RenderWindow& window) {
	const sf::Vector2f viewCenter = window.getView().getCenter();
	const sf::Vector2f viewSize = window.getView().getSize();
	const sf::Vector2f lightPos = viewCenter;
	const float radius = std::max(viewSize.x, viewSize.y) * 0.6f;
	const float rangeSq = radius * radius;

	m_closeEdges.clear();
	for (const auto& edge : m_allEdges) {
		const sf::Vector2f p1 = edge.m_origin;
		const sf::Vector2f p2 = edge.point(1.f);
		const sf::Vector2f ab = p2 - p1;
		const sf::Vector2f ap = lightPos - p1;

		const float abDotAb = ab.x * ab.x + ab.y * ab.y;
		if (abDotAb == 0) continue;

		const float t = std::max(0.f, std::min(1.f, (ap.x * ab.x + ap.y * ab.y) / abDotAb));
		const sf::Vector2f closestPoint = p1 + ab * t;

		const float dx = closestPoint.x - lightPos.x;
		const float dy = closestPoint.y - lightPos.y;
		const float distSq = dx * dx + dy * dy;

		if (distSq <= rangeSq) {
			m_closeEdges.push_back(edge);
		}
	}
}

//-------------------------------------
// Debug: Draw all edges and close edges in different colors
void World::DebugEdge(sf::RenderWindow& window) {
	for (const auto& edge : m_allEdges) {
		const sf::Vector2f p1 = edge.m_origin;
		const sf::Vector2f p2 = edge.point(1.f);
		const sf::Vector2f direction = p2 - p1;
		const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		sf::RectangleShape rect;
		rect.setSize({ length, 2.f });
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(p1);
		rect.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159f);
		window.draw(rect);
	}

	for (const auto& edge : m_closeEdges) {
		const sf::Vector2f p1 = edge.m_origin;
		const sf::Vector2f p2 = edge.point(1.f);
		const sf::Vector2f direction = p2 - p1;
		const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		sf::RectangleShape rect;
		rect.setSize({ length, 3.f });
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(p1);
		rect.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159f);
		window.draw(rect);
	}
}
