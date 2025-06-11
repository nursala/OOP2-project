#pragma once
// Controller.h
#include "SFML/Graphics.hpp"
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
	void setScreen(ScreenID screen);
	void removeScreen();

private:

	void processEvents();
	void update();
	void render();
	////////////////////////////////
	std::stack <std::unique_ptr<Screen>> m_screens;
	////////////////////////////////
	sf::Clock m_clock;
	sf::RenderWindow m_window;
	std::function<void(ScreenID)> m_changeScreen;
	std::optional<ScreenID> m_nextScreen;
};