#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class LoadGame : public Screen {
public:
	LoadGame();
	virtual ~LoadGame() = default;
	void init() override;
	void update(sf::RenderWindow& window, float dt) override;
	Constants::ScreenID getScreenID() const override;
private:
	float m_timer;
};