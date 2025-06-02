#pragma once

#include "SFML/Graphics.hpp"
#include "PlayGround.h"
#include "ScreensInc/Screen.h"
#include "AnimationInc/Animation.h"

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
	sf::Texture m_texture;
	sf::Sprite m_spriteSheet;
	Animation m_animation;
};


