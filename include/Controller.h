#pragma once

#include "SFML/Graphics.hpp"
#include "ScreensInc/Screen.h"
#include <box2d/box2d.h>
#include "GameObject/Player.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "GameObject/Enemy.h"
#include <stack>

#include "Candle/LightingArea.hpp"
// حذف RadialLight لأنه استُبدل
//#include "Candle/RadialLight.hpp"

#include "VisionLight.h" // ✅ كلاس الرؤية المخصص الجديد

class Controller
{
public:
    Controller();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::Clock m_clock;
    sf::View m_view;
    sf::RenderWindow m_window;
    b2World m_world;
    std::unique_ptr<Player> m_player;
    sf::Texture m_mapTexture;
    LoadMap m_tileMap;
    DebugDraw m_debugDraw;
    std::unique_ptr<Enemy> m_enemy;
    sf::Sprite m_mapSprite;

    // ✅ استبدال RadialLight بـ VisionLight
    VisionLight m_visionLight;
	candle::RadialLight m_radialLight; // لا يزال موجودًا إذا كنت بحاجة إليه
    candle::EdgeVector m_lightEdges;
    candle::LightingArea m_lightingArea;

    std::unordered_set<b2Fixture*> hitFixtures;
    std::vector<candle::Edge> closeEdges;



    static constexpr float SCALE = 30.f;
};
