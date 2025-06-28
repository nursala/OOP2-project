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
#include "RenderLayers.h"

class World {
public:
    World();
    void update(sf::RenderWindow& , float );
    void render(sf::RenderWindow& );
    const sf::Vector2f getMapTextureSize() const;
    const Player& getPlayer() const;
    b2World& getWorld();
    void addBullets(std::vector<std::unique_ptr<Bullet>> );
    std::vector<candle::Edge>& getCloseEdges() { return m_closeEdges; };
    std::vector<Enemy*> getEnemies() const;
private:
    void initWorld();
	void createGifts();
    void loadMapTexture();
    void createPlayer();
    void createGift(GiftType , b2Vec2 );
    void createEnemy();
    void setupMap();
    void updateBullets(float );
    void buildAllEdges();
    void calcNearlyEdge(sf::RenderWindow& );
    void DebugEdge(sf::RenderWindow& );

    b2World m_world;
    std::unique_ptr<RenderLayers> m_renderLayers;
    std::shared_ptr<Player> m_player;
    std::vector <std::shared_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Gift>> m_gifts;
    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;
    sf::Clock m_clock;
    sf::Clock m_movementClock;
    LoadMap m_tileMap;
    candle::EdgeVector m_allEdges;
    std::vector<candle::Edge> m_closeEdges;
    static constexpr float SCALE = 30.f;
};
