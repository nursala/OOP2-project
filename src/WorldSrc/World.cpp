#include "WorldInc/World.h"
#include "GameObject/ContactListener.h" // Ensure this header is included
#include "GameObject/Gift.h" // Ensure this include is present
#include "GameObject/ExtraHealthGift.h"
#include "GameObject/ExtraArmorGift.h"
#include "GameObject/EnemySpDwGift.h"
#include "GameObject/SpeedUpGift.h"
#include "GameObject/SpyGift.h"
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

void World::initWorld()
{
    loadMapTexture();
    createPlayer();
    createEnemy();
    createGifts();
    setupMap();
    buildAllEdges();
    setupPlayerLight();
}

void World::loadMapTexture()
{
    if (!m_mapTexture.loadFromFile("map.png")) {
        throw std::runtime_error("Failed to load map.png!");
    }
    m_mapSprite.setTexture(m_mapTexture);
    m_world.SetContactListener(new ContactListener());
    Factory::instance().registerType<Player>(TextureID::Player, std::ref(*this));
}

void World::createPlayer()
{
    Factory::instance().registerType<Player>(TextureID::Player, std::ref(*this));
    m_player = Factory::instance().createAs<Player>(TextureID::Player);
	sf::Vector2f pos = m_tileMap.getPlayerSpawns();
    m_player->setPostion(b2Vec2(pos.x, pos.y));
    m_player->init();
}

void World::createGifts()
{
	auto giftPositions = m_tileMap.getGiftSpawns();
	for (const auto& pos : giftPositions)
	{
        createGift(static_cast<GiftType>(rand() % 5), b2Vec2(pos.x, pos.y));
	}
}

void World::createGift(GiftType type,b2Vec2 pos)
{
	sf::Vector2f tempPos(pos.x * SCALE, pos.y * SCALE);
	switch (type)
	{
	case GiftType::ARMOR:
		Factory::instance().registerType<ExtraArmorGift>(TextureID::ARMOR, std::ref(*this),tempPos);
		m_gifts.push_back(Factory::instance().createAs<ExtraArmorGift>(TextureID::ARMOR));
		break;
	case GiftType::HEALTH:
		Factory::instance().registerType<ExtraHealthGift>(TextureID::HEALTH, std::ref(*this),tempPos);
		m_gifts.push_back(Factory::instance().createAs<ExtraHealthGift>(TextureID::HEALTH));
		break;
	case GiftType::ENEMYSPEEDDOWN:
		Factory::instance().registerType<EnemySpDwGift>(TextureID::ENEMYSPEEDDOWN, std::ref(*this),tempPos);
		m_gifts.push_back(Factory::instance().createAs<EnemySpDwGift>(TextureID::ENEMYSPEEDDOWN));
		break;
	case GiftType::SPEEDUP:
		Factory::instance().registerType<SpeedUpGift>(TextureID::SPEEDUP, std::ref(*this), tempPos);
		m_gifts.push_back(Factory::instance().createAs<SpeedUpGift>(TextureID::SPEEDUP));
		break;
	case GiftType::SPY:
		Factory::instance().registerType<SpyGift>(TextureID::SPY, std::ref(*this), tempPos);
		m_gifts.push_back(Factory::instance().createAs<SpyGift>(TextureID::SPY));
		break;
	default:
		throw std::runtime_error("Unknown GiftType");
	}
	m_gifts.back()->init();
	m_gifts.back()->setPostion(pos);

//}
   /* Factory::instance().registerType<Gift>(
        TextureID::Life,
        std::ref(*this),
        TextureManager::instance().get(TextureID::Life),
        sf::Vector2f{ 200, 200 }
    );
    m_gift = Factory::instance().createAs<Gift>(TextureID::Life);
}*/
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

    for (int i = 0; i < enemyPositions.size(); ++i)
    {
        int randomIQ = rand() % 10 + 1;

        auto enemy = Factory::instance().createAs<Enemy>(TextureID::Enemy);
        enemy->setPostion(b2Vec2(enemyPositions[i].x, enemyPositions[i].y));
        enemy->init();           
        m_enemies.push_back(std::move(enemy));
    }
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
    for (auto& enemy : m_enemies)
    {
        enemy->update(deltaTime);
    }

    for (auto& bullet : m_bullets)
    {
        bullet->update(deltaTime);
    }
	for (auto& gift : m_gifts)
	{
        //std::cout << gift->getPositionB2().x << ", " << gift->getPositionB2().y << std::endl;
        if (gift->isDestroyed())
        {
            m_gifts.erase(std::remove_if(m_gifts.begin(), m_gifts.end(),
                [](const std::unique_ptr<Gift>& g) { return g->isDestroyed(); }), m_gifts.end());
        }
	}
    updateLightSystem(window);
    updateBullets(deltaTime);
    //updateLightSystem(window);
}

void World::updateBullets(float deltaTime)
{
    for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
        (*it)->update(deltaTime);

        if ((*it)->shouldDestroy()) {
            m_world.DestroyBody((*it)->getBody());
            it = m_bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void World::updateLightSystem(sf::RenderWindow& window)
{
    sf::Vector2f playerPos = m_player->getPosition();
    sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    float angleToMouse = std::atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x);

    calcNearlyEdge(window);
    m_light.update(playerPos, mouseWorld);
    m_light.updateCastLight(m_closeEdges, m_world);
    sf::Vector2f topLeft = window.getView().getCenter() - window.getView().getSize() / 2.f;
    m_light.setPosition(topLeft);
}

void World::render(sf::RenderWindow& window)
{
    window.draw(m_mapSprite);
    m_light.drawFinalLights(window);

    m_player->render(window);

    for (auto& enemy : m_enemies)
    {
        enemy->render(window);
    }

    for (auto& gift : m_gifts)
    {
        if (gift->isVisible())
            gift->render(window);
    }
    for (auto& bullet : m_bullets)
    {
        bullet->render(window);
    }

    //m_gift->render(window);

    m_light.drawLights(window);
    //DebugEdge(window);
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
        bullet->init();
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
