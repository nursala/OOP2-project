#pragma once

#include "ScreensInc/Screen.h"

class Help : public Screen {

public:
	Help();
	void init();
	void processEvent(sf::Event& event, sf::RenderWindow& window) override;
	Constants::ScreenID getScreenID() const override;
	void render(sf::RenderWindow& window) override;
private:
	sf::View m_view;
	float m_scrollSpeed = 50.0f;

	void clampView();

};