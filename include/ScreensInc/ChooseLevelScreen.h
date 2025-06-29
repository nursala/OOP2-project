#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class ChooseLevelScreen : public Screen {

public:
	ChooseLevelScreen();
	~ChooseLevelScreen() = default;
	Constants::ScreenID getScreenID() const override;
	void render(sf::RenderWindow& window) override;
private:
	std::vector <sf::RectangleShape> m_level;
	void init() override;
};
