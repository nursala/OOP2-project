#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class PlayGround : public Screen {
public:
	PlayGround();
	virtual ~PlayGround() = default;
	void processEvent(sf::Event& event, sf::RenderWindow& window) override;
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window) override;
private:
	void initButtons();
	sf::Font m_font;
	sf::Text m_title;
};