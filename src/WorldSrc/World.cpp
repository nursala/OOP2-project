#include "WorldInc/World.h"
#include <iostream>
#include <cmath>
#include "Factory.h"

World::World()
    : m_world(b2Vec2(0.f, 0.f)),
    m_tileMap("map.json"),
    m_light({ 2400, 2400 })
{
    initWorld();
    loadMapTexture();
    createPlayer();
    createEnemy();
    setupMap();
    buildAllEdges();
    setupPlayerLight();
}

void World::initWorld()
{
    m_mapSprite.setTexture(m_mapTexture);
}

void World::loadMapTexture()
{
    if (!m_mapTexture.loadFromFile("map.png")) {
        throw std::runtime_error("Failed to load map.png!");
    }
}

void World::createPlayer()
{
    Factory::instance().registerType<Player>(TextureID::Player, std::ref(*this));
    m_player = Factory::instance().createAs<Player>(TextureID::Player);
    m_player->setPostion({ 10, 10 });
}

void World::createEnemy()
{
    int randomIQ = rand() % 10 + 1;
    Factory::instance().registerType<Enemy>(TextureID::Enemy,
        std::ref(*this),
        std::cref(m_tileMap),
        std::cref(*m_player),
        randomIQ);

    m_enemy = Factory::instance().createAs<Enemy>(TextureID::Enemy);
}

void World::setupMap()
{
    m_tileMap.createCollisionObjects(m_world, "walls");
}

void World::setupPlayerLight()
{
    m_player->setLight(m_light.getPlayerVision());
    m_player->setWeaponLight(m_light.getWeaponLight());
}

void World::update(sf::RenderWindow& window, float deltaTime)
{
    m_world.Step(deltaTime, 8, 3);
    m_player->update(deltaTime);
    m_enemy->update(deltaTime);
    for (auto& bullet : m_bullets)
    {
        bullet->update(deltaTime);
    }
    updateLightSystem(window);
}

void World::updateLightSystem(sf::RenderWindow& window)
{
    sf::Vector2f playerPos = m_player->getPosition();
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    float angleToMouse = std::atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x);

    calcNearlyEdge();
    m_light.update(playerPos, mouseWorld);
    m_light.updateCastLight(m_closeEdges, m_world);
    sf::Vector2f topLeft = window.getView().getCenter() - window.getView().getSize() / 2.f;
    m_light.setPosition(topLeft);
}

void World::render(sf::RenderWindow& window)
{
    drawMap(window);
    drawLighting(window);
    drawGameObjects(window);
}

void World::drawMap(sf::RenderWindow& window)
{
    window.draw(m_mapSprite);
}

void World::drawLighting(sf::RenderWindow& window)
{
    m_light.drawFinalLights(window);
    m_light.drawLights(window);
}

void World::drawGameObjects(sf::RenderWindow& window)
{
    m_player->render(window);
    m_enemy->render(window);
    for (auto& bullet : m_bullets)
    {
        bullet->render(window);
    }
}

b2World& World::getWorld()
{
    return m_world;
}

void World::addBullet(std::unique_ptr<Bullet> bullet)
{
	if (bullet) {
		bullet->setPostion(bullet->getPositionB2());
		m_bullets.push_back(std::move(bullet));
	}
}

const sf::Vector2f World::getMapTextureSize() const
{
    if (!m_mapTexture.getSize().x || !m_mapTexture.getSize().y) {
        return sf::Vector2f(0.f, 0.f);
    }
    return sf::Vector2f(static_cast<float>(m_mapTexture.getSize().x), static_cast<float>(m_mapTexture.getSize().y));
}

const Player& World::getPlayer() const
{
    return *m_player;
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

void World::calcNearlyEdge()
{
    sf::Vector2f lightPos = m_light.getPlayerVision()->getPosition();
    float rangeSq = m_light.getPlayerVision()->getRange() * m_light.getPlayerVision()->getRange();

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
