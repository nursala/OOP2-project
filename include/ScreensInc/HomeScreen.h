#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class HomeScreen : public Screen {
public:
	HomeScreen();
	virtual ~HomeScreen() = default;
private:
	void initButtons();
	sf::Font m_font;
	sf::Text m_title;
};