#pragma once
// Controller.h
#include "SFML/Graphics.hpp"
#include "PlayGround.h"
#include "ScreensInc/Screen.h"
#include <box2d/box2d.h>
#include "GameObject/Player.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "LightSystem.h"
#include "GameObject/Enemy.h"
#include <stack>

class  Controller
{
public:
	 Controller();
	 void run();
	
private:

	void processEvents();
	void update();
	void render();
	////////////////////////////////
	std::stack <std::unique_ptr<Screen>> m_screens;
	////////////////////////////////
	sf::Clock m_clock;
	sf::View m_view;
	sf::RenderWindow m_window;
	b2World m_world;
	std::unique_ptr<Player> m_player;
	sf::Texture m_mapTexture;
	LoadMap m_tileMap;
	DebugDraw m_debugDraw;
	LightSystem m_light; 
	std::unique_ptr<Enemy> m_enemy; 
	sf::Sprite m_mapSprite;
	static constexpr float SCALE = 30.f;

};


