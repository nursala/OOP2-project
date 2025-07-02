#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <stack>
#include <memory>
#include <optional>
#include <functional>

#include "ScreensInc/Screen.h"
#include "GameObject/Player.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "LightSystem.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"

class Controller {
public:
    // Singleton access
    static Controller& getInstance();

    void run();
    void pushScreen(std::unique_ptr<Screen> screen);
    const sf::Font& getFont();
    void setPopFlag();
    void setPopFlagToHome();
    void popScreen();
private:
    Controller();
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    // Main loop helpers
    void processEvents();
    void update();
    void render();
    void popToHome();
	bool m_shouldPopToHome = false;
    bool m_shouldPop = false;
    std::stack<std::unique_ptr<Screen>> m_screens;
    sf::Clock m_clock;
    sf::RenderWindow m_window;
	sf::Font m_font; // Font for UI elements
};