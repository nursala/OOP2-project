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

class World
{
public:
	World();
	void update(sf::RenderWindow& window, float deltaTime);
	void render(sf::RenderWindow& window);
	const sf::Vector2f getPlayerPixels() const;
	const sf::Vector2f getMapTextureSize() const;
	const Player& getPlayer() const;
    b2World m_world;

private:
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Enemy> m_enemy;
	std::unique_ptr<Gift> m_gift; 

    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;
    LoadMap m_tileMap;

    LightSystem m_light;

    candle::EdgeVector m_allEdges;         // كل الحواف في العالم (مرة واحدة عند البداية)
    std::vector<candle::Edge> m_closeEdges; // الحواف القريبة من مصدر الضوء (تتغير كل فريم)

    static constexpr float SCALE = 30.f;
    
    void calcNearlyEdge();
    void DebugEdge(sf::RenderWindow& window);
    void buildAllEdges();  // دالة تبني الحواف من العالم عند البداية
};
