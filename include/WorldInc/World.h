#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "LightSystem.h"
#include <vector>
#include <memory>
#include "GameObject/Bullet.h"

class World
{
public:
    World();
    void update(sf::RenderWindow& window, float deltaTime);
    void render(sf::RenderWindow& window);
    const sf::Vector2f getMapTextureSize() const;
    const Player& getPlayer() const;
    b2World& getWorld();
	void addBullet(std::unique_ptr<Bullet> bullet);
private:

    void initWorld();
    void loadMapTexture();
    void createPlayer();
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
    //void calcNearlyEdge();
    void DebugEdge(sf::RenderWindow& window);

private:
    b2World m_world;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Enemy> m_enemy;
	std::vector<std::unique_ptr<Bullet>> m_bullets;

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
