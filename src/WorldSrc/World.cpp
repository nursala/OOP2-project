// ===== World.cpp =====
#include "WorldInc/World.h"
#include "GameObject/ContactListener.h"
#include "GameObject/Gift.h"
#include <iostream>
#include <cmath>
#include "Factory.h"

World::World()
    : m_world(b2Vec2(0.f, 0.f)),
    m_tileMap("map.json"),
    m_light({ 2400, 2400 })
{
    initWorld();
}

void World::initWorld() {

    loadMapTexture();
    createPlayer();
    createEnemy();
    createGifts();
    setupMap();
    buildAllEdges();
    setupPlayerLight();
}

void World::loadMapTexture() {
    if (!m_mapTexture.loadFromFile("map.png")) {
        throw std::runtime_error("Failed to load map.png!");
    }
    m_mapSprite.setTexture(m_mapTexture);
    m_world.SetContactListener(new ContactListener(*this));
    Factory::instance().registerType<Player>(TextureID::Player, std::ref(*this));
}

void World::createPlayer() {

    m_player = Factory::instance().createAs<Player>(TextureID::Player);
	sf::Vector2f pos = m_tileMap.getPlayerSpawns();
    m_player->setPosition(b2Vec2(pos.x, pos.y));
    m_player->init();
}

void World::createGifts()
{
    int begin = static_cast<int>(TextureID::ARMOR);
    for (int i = begin; i < static_cast<int>(TextureID::SIZE); i++) {
        Factory::instance().registerType<Gift>(TextureID(i), std::ref(*this), TextureManager::instance().get(TextureID(i)));
    }
	auto giftPositions = m_tileMap.getGiftSpawns();
	int giftsTypeCount = static_cast<int>(GiftType::SIZE);
	for (const auto& pos : giftPositions)
	{
        createGift(static_cast<GiftType>(rand() % giftsTypeCount), b2Vec2(pos.x, pos.y));
        //createGift(GiftType::SPY, b2Vec2(pos.x, pos.y));
	}
}

void World::createGift(GiftType type,b2Vec2 pos)
{
    auto textureId = static_cast<TextureID>(static_cast<int>(type)+2);
    m_gifts.push_back(Factory::instance().createAs<Gift>(textureId));
    m_gifts.back()->setType(type);
    m_gifts.back()->init();
    m_gifts.back()->setPosition(pos);
	//m_gifts.back()->setSpriteRadius(0.5f); // Set the radius for the gift
}

void World::createEnemy()
{
	auto enemyPositions = m_tileMap.getEnemySpawns();

    Factory::instance().registerType<Enemy>(
        TextureID::Enemy,
        std::ref(*this),
        std::cref(m_tileMap),
        std::cref(*m_player)
    );
	//std::cout << "Enemies size: " << enemyPositions.size() << std::endl;
    for (int i = 0; i < enemyPositions.size(); ++i)
    {
        //int randomIQ = rand() % 10 + 1;

        auto enemy = Factory::instance().createAs<Enemy>(TextureID::Enemy);
        enemy->setPosition(b2Vec2(enemyPositions[i].x, enemyPositions[i].y));
        enemy->init();           
        m_enemies.push_back(std::move(enemy));
    }
}

void World::setupMap() {
    m_tileMap.createCollisionObjects(m_world, "walls");
}

void World::setupPlayerLight() {
    m_player->setLight(m_light.getPlayerVision());
    m_player->setWeaponLight(m_light.getWeaponLight());
}

void World::update(sf::RenderWindow& window, float deltaTime) {
    m_world.Step(deltaTime, 8, 3);
    m_player->update(deltaTime);
    for (auto& enemy : m_enemies)
    {
        enemy->update(deltaTime);
    }

    for (auto& bullet : m_bullets)
        bullet->update(deltaTime);
    for (auto it = m_gifts.begin(); it != m_gifts.end(); ) {
		//std::cout << "radius: " << (*it)->getSpriteRadius().x << " " << (*it)->getSpriteRadius().y << std::endl;
		
        if ((*it)->isDestroyed()) {
            m_world.DestroyBody((*it)->getBody());
            it = m_gifts.erase(it);
        }
        else ++it;
    }
    updateLightSystem(window);
    updateBullets(deltaTime);
}

void World::updateBullets(float deltaTime) {
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        (*it)->update(deltaTime);
        if ((*it)->shouldDestroy()) {
            m_world.DestroyBody((*it)->getBody());
            it = m_bullets.erase(it);
        }
        else ++it;
    }
}

void World::updateLightSystem(sf::RenderWindow& window) {
    sf::Vector2f playerPos = m_player->getPosition();
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    //float angleToMouse = std::atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x);
    calcNearlyEdge(window);
    m_light.update(playerPos, mouseWorld);
    m_light.updateCastLight(m_closeEdges, m_world);
    sf::Vector2f topLeft = window.getView().getCenter() - window.getView().getSize() / 2.f;
    m_light.setPosition(topLeft);
}

void World::render(sf::RenderWindow& window) {

    window.draw(m_mapSprite);
    m_player->render(window);

    for (auto& enemy : m_enemies)
        enemy->render(window);

    for (auto& gift : m_gifts)
        if (gift->isVisible()) gift->render(window);
    for (auto& bullet : m_bullets)
        bullet->render(window);
    m_light.drawLights(window);
    DebugEdge(window);
}

void World::drawMap(sf::RenderWindow& window) {
    window.draw(m_mapSprite);
}

void World::drawLighting(sf::RenderWindow& window) {
    m_light.drawFinalLights(window);
    m_light.drawLights(window);
}

void World::drawGameObjects(sf::RenderWindow& window) {
    m_player->render(window);
    for (auto& bullet : m_bullets)
        bullet->render(window);
}

b2World& World::getWorld() {
    return m_world;
}

void World::addBullets(std::vector<std::unique_ptr<Bullet>> bullets) {
    for (auto& bullet: bullets)
    {
        bullet->init();
        m_bullets.push_back(std::move(bullet));
    }
}

const sf::Vector2f World::getMapTextureSize() const {
    if (!m_mapTexture.getSize().x || !m_mapTexture.getSize().y)
        return sf::Vector2f(0.f, 0.f);
    return sf::Vector2f(static_cast<float>(m_mapTexture.getSize().x), static_cast<float>(m_mapTexture.getSize().y));
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
    sf::Vector2f viewCenter = window.getView().getCenter();   // مركز المشهد
    sf::Vector2f viewSize = window.getView().getSize();       // حجم المشهد

    sf::Vector2f lightPos = viewCenter;
    float radius = std::max(viewSize.x, viewSize.y) * 0.6f; // مجال أوسع قليلًا من الشاشة
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