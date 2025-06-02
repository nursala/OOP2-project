#pragma once

#include "SFML/Graphics.hpp"
#include "PlayGround.h"
#include "ScreensInc/Screen.h"

class  Controller
{
public:
	 Controller();
	 void run();
	
private:

	void processEvents();
	void update();
	void render();


	sf::RenderWindow m_window;
	sf::RectangleShape m_shape;
};


