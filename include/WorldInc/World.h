#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject/Player.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "LightSystem.h"
#include "GameObject/Enemy.h"
#include <memory>
//// World.h
class World
{
public:
	World();
	void update(sf::RenderWindow& window, float deltaTime);
	void render(sf::RenderWindow& window);
	const sf::Vector2f getPlayerPixels() const;
	const sf::Vector2f getMapTextureSize() const;
	const Player& getPlayer() const;
private:
	b2World m_world;
	std::unique_ptr<Player> m_player;
	sf::Texture m_mapTexture;
	LoadMap m_tileMap;
	//DebugDraw m_debugDraw;
	LightSystem m_light;
	std::unique_ptr<Enemy> m_enemy;
	sf::Sprite m_mapSprite;
	static constexpr float SCALE = 30.f;
};
