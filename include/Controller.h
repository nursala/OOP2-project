#pragma once

#include "SFML/Graphics.hpp"
#include "PlayGround.h"
#include "ScreensInc/Screen.h"
#include <box2d/box2d.h>
#include "GameObject/Player.h"

class  Controller
{
public:
	 Controller();
	 void run();
	
private:

	void processEvents();
	void update();
	void render();

	sf::Clock m_clock;
	sf::RenderWindow m_window;
	b2World m_world;
	Player m_player;
};


