#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "LightSystem.h"
#include "GameObject/Bullet.h"
#include <vector>
#include <memory>

class World {
public:
    World();

    void update(sf::RenderWindow& window, float deltaTime);
    void render(sf::RenderWindow& window);

    const sf::Vector2f getMapTextureSize() const;
    const Player& getPlayer() const;
    b2World& getWorld();
    void addBullets(std::vector<std::unique_ptr<Bullet>> bullets);

    std::vector<Enemy*> getEnemies() const;

private:
    void initWorld();
	void createGifts();
    void loadMapTexture();
    void createPlayer();
    void createGift(GiftType type, b2Vec2 pos);
    void createEnemy();
    void setupMap();
    void setupPlayerLight();
    void updateLightSystem(sf::RenderWindow& window);
    void drawMap(sf::RenderWindow& window);
    void drawGameObjects(sf::RenderWindow& window);
    void drawLighting(sf::RenderWindow& window);
    void updateBullets(float deltaTime);
    void buildAllEdges();
    void calcNearlyEdge(sf::RenderWindow& window);
    void DebugEdge(sf::RenderWindow& window);

    b2World m_world;
    std::unique_ptr<Player> m_player;
    std::vector <std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Gift>> m_gifts;

    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;
    sf::Clock m_clock;
    sf::Clock m_movementClock;
    float m_elapsedTime;
    LoadMap m_tileMap;
    LightSystem m_light;
    candle::EdgeVector m_allEdges;
    std::vector<candle::Edge> m_closeEdges;

    static constexpr float SCALE = 30.f;
};
